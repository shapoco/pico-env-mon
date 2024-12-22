#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

#include <nyna/graphics/graphics.hpp>
#include <nyna/ls027b4/pico/driver.hpp>

#include "images/images.hpp"
#include "fonts/fonts.hpp"

#include "graph.hpp"

#include "bme280.hpp"

#include "mhz19c.hpp"

namespace picoenvmon {

namespace g = nyna::graphics;

static const int FIRM_VER_MAJOR = 0;
static const int FIRM_VER_MINOR = 4;

static const int LOGO_DISPLAY_TIME_MS = 5000;

static const int SAMPLING_INTERVAL_MS = 5000;

static const int GRAPH_TIME_RANGE_H = 24;
//static const int GRAPH_TIME_RANGE_H = 1;
static const int GRAPH_SHIFT_INTERVAL_MS = GRAPH_TIME_RANGE_H * 3600 * 1000 / Graph::DEPTH;

// 温度は湿度・気圧の補正用であり気温よりやや高いため適当に補正する
// 補正値の適正値はセンサの使用条件により異なる
static const float TEMPERATURE_OFFSET = -1.5f;

g::Bitmap1bpp screen(nyna::ls027b4::SCREEN_WIDTH, nyna::ls027b4::SCREEN_HEIGHT);
nyna::ls027b4::pico::Driver lcd(spi_default, 20, 22, 21);

BME280 bme280(spi_default, 17);
MHZ19C mhz19c(uart0, 0, 1);

Graph graph_t(0, 0, 1.0f); // temperature
Graph graph_h(0, 60, 10.0f); // humidity
Graph graph_p(0, 120, 1.0f); // pressure
Graph graph_c(0, 180, 10.0f); // CO2

static void sample(bool shift);
static void renderTrack(Graph &graph, float currVal, const char* currValFmt, const char* unitStr, const char* unitFmt);
static void renderSplash();

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
    lcd.write(screen);
    lcd.service();
    lcd.disp_on();

    printf("START...\n"); // todo

    uint64_t t_now = time_us_64();
    uint64_t t_next_sample = t_now;
    uint64_t t_next_shift = t_now;
    uint64_t t_logo_expire = t_now + LOGO_DISPLAY_TIME_MS * 1000;

    while (true) {
        t_now = time_us_64();
        
        // sampling timing
        if (t_now >= t_next_sample) {
            printf("SAMPLE\n"); // todo
            t_next_sample += SAMPLING_INTERVAL_MS * 1000;

            // graph shift timing
            bool shift = t_now >= t_next_shift;
            if (shift) {
                printf("  SHIFT\n"); // todo
                t_next_shift += GRAPH_SHIFT_INTERVAL_MS * 1000;
            }

            sample(shift);
            printf("b\n"); // todo

            if (t_now < t_logo_expire) {
                renderSplash();
            }
            printf("c\n"); // todo
        }

        // LCD update
        lcd.write(screen);
        lcd.service();
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
    graph_c.push((float)co2, shift);
    
    int x_value = 250;
    char s[8];

    absolute_time_t t_start = get_absolute_time();

    screen.clear(1);

    renderTrack(graph_t, temperature, "%-.1f", "\xDF""C", "%-.1f %-.1f/%-.1f");
    renderTrack(graph_h, humidity, "%-.1f", "%", "%-.1f %-.1f/%-.1f");
    renderTrack(graph_p, pressure, "%-.0f", "hpA", "%-.1f %-.0f/%-.0f");
    renderTrack(graph_c, (float)co2, "%-.0f", "ppm", "%-.0f %-.0f/%-.0f");

    absolute_time_t t_end = get_absolute_time();

    // show screen update time
    //int64_t t_elapsed_us = absolute_time_diff_us(t_start, t_end);
    //sprintf(s, "%ld", t_elapsed_us);
    //digit16_draw_string(screen, 0, 0, s);
}

static void renderTrack(Graph &graph, float currVal, const char* currValFmt, const char* unitStr, const char* mimMaxFmt) {
    int x_value = 250;
    char s[8];

    int y = graph.top;
    int x_unit;

    // graph
    graph.render(screen);

    // current value
    sprintf(s, currValFmt, currVal);
    x_unit = screen.drawString(fonts::pemsans32, x_value, y + 4, s, g::BLACK);
    screen.drawString(fonts::pemsans24, x_unit, y + 15, unitStr, g::BLACK);

    // scale, min/max
    screen.drawBitmap(x_value, y + 40, images::step);
    sprintf(s, mimMaxFmt, graph.horizontal_line_step, graph.total_max, graph.total_min);
    screen.drawString(g::fonts::shaposans22b, x_value + images::step.width + 2, y + 39, s, g::BLACK);

    // horizontal line
    screen.fillRect(0, y + graph.HEIGHT - 1, screen.width, 1, g::BLACK);
}

static void renderSplash() {
    static constexpr int PADDING = 10;

    const g::TinyFont &font = g::fonts::shaposans22b;

    int w = images::logo.width + PADDING * 2;
    int h = images::logo.height + font.height + PADDING * 2 + PADDING / 2;
    int x0 = (screen.width - w) / 2;
    int y0 = (screen.height - h) / 2;
    
    screen.fillRect(x0 - 1, y0 - 1, w + 2, h + 2, g::WHITE);
    screen.drawRect(x0, y0, w - 1, h - 1, g::BLACK);
    
    screen.drawBitmap(x0 + PADDING, y0 + PADDING, images::logo);

    char s[8];
    sprintf(s, "v%d.%d", FIRM_VER_MAJOR, FIRM_VER_MINOR);
    int sw = font.measureStringWidth(s);
    screen.drawString(font, x0 + (w - sw) / 2, y0 + PADDING * 3 / 2 + images::logo.height, s, g::BLACK);
}

}

int main() {
    return picoenvmon::main();
}

