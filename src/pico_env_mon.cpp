//#define PICO_DEFAULT_SPI 0
//#define PICO_DEFAULT_SPI_TX_PIN 19
//#define PICO_DEFAULT_SPI_RX_PIN 20
//#define PICO_DEFAULT_SPI_SCK_PIN 18

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

#include "mhz19c.hpp"

static const int LCD_TOGGLE_INTERVAL_MS = 500;

static const int SAMPLING_INTERVAL_MS = 5000;

static const int GRAPH_TIME_RANGE_H = 24;
static const int GRAPH_SHIFT_INTERVAL_MS = GRAPH_TIME_RANGE_H * 3600 * 1000 / Graph::DEPTH;

// 温度は湿度・気圧の補正用であり気温よりやや高いため適当に補正する
// 補正値の適正値はセンサの使用条件により異なる
static const float TEMPERATURE_OFFSET = -1.5f;

LcdScreen screen;
LcdDriver lcd(spi_default, 20, 22, 21);

BME280 bme280(spi_default, 17);
MHZ19C mhz19c(uart0, 0, 1);

Graph graph_t(0, 0, 1.0f); // temperature
Graph graph_h(0, 60, 10.0f); // humidity
Graph graph_p(0, 120, 1.0f); // pressure
Graph graph_c(0, 180, 10.0f); // CO2

static void sample(bool shift);

int main() {
    stdio_init_all();

    spi_init(spi_default, 2000 * 1000);
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);

    lcd.init();
    bme280.init();
    mhz19c.init();
    screen.clear(1);
    lcd.write(screen.data);
    lcd.disp_on();

    absolute_time_t t_next_lcd_toggle = make_timeout_time_ms(LCD_TOGGLE_INTERVAL_MS);
    int sampling_interval_counter = SAMPLING_INTERVAL_MS;
    int graph_shift_interval_counter = 0;

    while (true) {
        // keep interval
        sleep_until(t_next_lcd_toggle);
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
    int co2;
    mhz19c.measure(&co2);

    // enter new value to the graphs
    graph_t.push(temperature, shift);
    graph_h.push(humidity, shift);
    graph_p.push(pressure, shift);
    graph_c.push(co2, shift);
    
    int x_value = 245;
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
        sprintf(s, "%-.1f %-.1f/%-.1f", graph_t.horizontal_line_step, graph_t.total_min, graph_t.total_max);
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
        screen.draw_image(img_step, x_value, y + 40);
        sprintf(s, "%-.1f %-.1f/%-.1f", graph_h.horizontal_line_step, graph_h.total_min, graph_h.total_max);
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
        screen.draw_image(img_step, x_value, y + 40);
        sprintf(s, "%-.1f %-.0f/%-.0f", graph_p.horizontal_line_step, graph_p.total_min, graph_p.total_max);
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
        screen.draw_image(img_step, x_value, y + 40);
        sprintf(s, "%-.0f %-.0f/%-.0f", graph_c.horizontal_line_step, graph_c.total_min, graph_c.total_max);
        digit16_draw_string(screen, x_value + img_step.width + 2, y + 40, s);
    }

    absolute_time_t t_end = get_absolute_time();

    // show screen update time
    //int64_t t_elapsed_us = absolute_time_diff_us(t_start, t_end);
    //sprintf(s, "%ld", t_elapsed_us);
    //digit16_draw_string(screen, 0, 0, s);
}