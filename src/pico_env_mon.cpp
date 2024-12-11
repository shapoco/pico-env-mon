#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

#include "ls027b4dh01.hpp"
#include "images.hpp"
#include "digit16.hpp"
#include "digit32.hpp"

#include "graph.hpp"

#include "bme280.hpp"

#include "CO2Sensor.hpp"

static const int FIRM_VER_MAJOR = 0;
static const int FIRM_VER_MINOR = 4;

static const int LOGO_DISPLAY_TIME_MS = 5000;

static const int LCD_TOGGLE_INTERVAL_MS = 500;

static const int SAMPLING_INTERVAL_MS = 5000;

static const int GRAPH_TIME_RANGE_H = 24;
//static const int GRAPH_TIME_RANGE_H = 1;
static const int GRAPH_SHIFT_INTERVAL_MS = GRAPH_TIME_RANGE_H * 3600 * 1000 / Graph::DEPTH;

// 温度は湿度・気圧の補正用であり気温よりやや高いため適当に補正する
// 補正値の適正値はセンサの使用条件により異なる
static const float TEMPERATURE_OFFSET = -1.5f;

LcdScreen screen;
LcdDriver lcd(spi_default, 20, 22, 21);

BME280 bme280(spi_default, 17);
CO2Sensor co2_sensor(uart0, 0, 1, 9600);

Graph graph_t(0, 0, 1.0f); // temperature
Graph graph_h(0, 60, 10.0f); // humidity
Graph graph_p(0, 120, 1.0f); // pressure
Graph graph_c(0, 180, 10.0f); // CO2

static void sample(bool shift);
static void draw_logo();

int main() {
    stdio_init_all();

    spi_init(spi_default, 2000 * 1000);
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);

    // Reset LCD and show boot logo before waiting or hanging for sensors to initialise
    lcd.init();
    screen.clear(1);
    draw_logo();
    lcd.write(screen.data);
    lcd.disp_on();
    absolute_time_t t_logo_expire = make_timeout_time_ms(LOGO_DISPLAY_TIME_MS);

    bme280.init();

    co2_sensor.init();
    co2_sensor.ABC(false);

    absolute_time_t t_next_lcd_toggle = make_timeout_time_ms(LCD_TOGGLE_INTERVAL_MS);
    int sampling_interval_counter = SAMPLING_INTERVAL_MS;
    int graph_shift_interval_counter = 0;

    while (true) {
        // keep interval
        sleep_until(t_next_lcd_toggle);
        absolute_time_t t_now = get_absolute_time();
        t_next_lcd_toggle = delayed_by_ms(t_next_lcd_toggle, LCD_TOGGLE_INTERVAL_MS);
        
        sampling_interval_counter += LCD_TOGGLE_INTERVAL_MS;
        graph_shift_interval_counter += LCD_TOGGLE_INTERVAL_MS;

        // sampling timing
        if (sampling_interval_counter > SAMPLING_INTERVAL_MS) {
            sampling_interval_counter -= SAMPLING_INTERVAL_MS;

            // graph shift timing
            bool shift = false;
            if (graph_shift_interval_counter > GRAPH_SHIFT_INTERVAL_MS) {
                graph_shift_interval_counter -= GRAPH_SHIFT_INTERVAL_MS;
                shift = true;
            }

            sample(shift);

            if (absolute_time_diff_us(t_logo_expire, t_now) < 0) {
                draw_logo();
            }
        }

        // LCD update
        lcd.write(screen.data);
    }
}

static void sample(bool shift) {
    // read BME280
    float temperature, pressure, humidity;
    bme280.read_env(&temperature, &humidity, &pressure);
    temperature += TEMPERATURE_OFFSET;

    // read CO2
    int co2 = -1;
    co2_sensor.getCO2Reading(&co2);

    // enter new value to the graphs
    graph_t.push(temperature, shift);
    graph_h.push(humidity, shift);
    graph_p.push(pressure, shift);
    graph_c.push(co2, shift);
    
    int x_value = 250;
    char s[8];

    absolute_time_t t_start = get_absolute_time();

    screen.clear(1);

    // temperature
    {
        int y = graph_t.top;
        int x_unit;

        // graph
        graph_t.render(screen);

        // current value
        sprintf(s, "%-.1f", temperature);
        x_unit = digit32_draw_string(screen, x_value, y + 4, s);
        screen.draw_image(img_degc, x_unit, y + 16);

        // scale, min/max
        screen.draw_image(img_step, x_value, y + 40);
        sprintf(s, "%-.1f %-.1f/%-.1f", graph_t.horizontal_line_step, graph_t.total_max, graph_t.total_min);
        digit16_draw_string(screen, x_value + img_step.width + 2, y + 40, s);

        // horizontal line
        screen.fill_rect(0, y + graph_t.HEIGHT - 1, screen.width, 1, 0);
    }

    // humidity
    {
        int y = graph_h.top;
        int x_unit;

        // graph
        graph_h.render(screen);

        // current value
        sprintf(s, "%-.1f", humidity);
        x_unit = digit32_draw_string(screen, x_value, y + 4, s);
        screen.draw_image(img_percent, x_unit, y + 16);

        // scale, min/max
        screen.draw_image(img_step, x_value - 1, y + 40);
        sprintf(s, "%-.1f %-.1f/%-.1f", graph_h.horizontal_line_step, graph_h.total_max, graph_h.total_min);
        digit16_draw_string(screen, x_value + img_step.width + 2, y + 40, s);

        // horizontal line
        screen.fill_rect(0, y + graph_h.HEIGHT - 1, screen.width, 1, 0);
    }

    // pressure
    {
        int y = graph_p.top;
        int x_unit;

        // graph
        graph_p.render(screen);

        // current value
        sprintf(s, "%-.0f", pressure);
        x_unit = digit32_draw_string(screen, x_value, y + 4, s);
        screen.draw_image(img_hpa, x_unit, y + 16);

        // scale, min/max
        screen.draw_image(img_step, x_value - 1, y + 40);
        sprintf(s, "%-.1f %-.0f/%-.0f", graph_p.horizontal_line_step, graph_p.total_max, graph_p.total_min);
        digit16_draw_string(screen, x_value + img_step.width + 2, y + 40, s);

        // horizontal line
        screen.fill_rect(0, y + graph_p.HEIGHT - 1, screen.width, 1, 0);
    }

    // CO2
    {
        int y = graph_c.top;
        int x_unit;

        // graph
        graph_c.render(screen);

        // current value
        sprintf(s, "%d", co2);
        x_unit = digit32_draw_string(screen, x_value, y + 4, s);
        screen.draw_image(img_ppm, x_unit, y + 16);

        // scale, min/max
        screen.draw_image(img_step, x_value - 1, y + 40);
        sprintf(s, "%-.0f %-.0f/%-.0f", graph_c.horizontal_line_step, graph_c.total_max, graph_c.total_min);
        digit16_draw_string(screen, x_value + img_step.width + 2, y + 40, s);
    }

    absolute_time_t t_end = get_absolute_time();

    // show screen update time
    //int64_t t_elapsed_us = absolute_time_diff_us(t_start, t_end);
    //sprintf(s, "%ld", t_elapsed_us);
    //digit16_draw_string(screen, 0, 0, s);
}

static void draw_logo() {
    static constexpr int PADDING = 10;
    int w = img_logo.width + PADDING * 2;
    int h = img_logo.height + img_digit16.height + PADDING * 2 + PADDING / 2;
    int x0 = (SCREEN_WIDTH - w) / 2;
    int y0 = (SCREEN_HEIGHT - h) / 2;
    
    screen.fill_rect(x0 - 1, y0 - 1, w + 2, h + 2, 1);
    screen.draw_rect(x0, y0, w - 1, h - 1, 0);
    
    screen.draw_image(img_logo, x0 + PADDING, y0 + PADDING);

    char s[8];
    sprintf(s, "v%d.%d", FIRM_VER_MAJOR, FIRM_VER_MINOR);
    int sw = digit16_measure_width(s) - DIGIT16_GAP;
    digit16_draw_string(screen, x0 + (w - sw) / 2, y0 + PADDING * 3 / 2 + img_logo.height, s);
}
