#pragma once

#include <stdint.h>
#include <math.h>

#include <nyna/graphics/graphics.hpp>

#include "images/images.hpp"

namespace picoenvmon {

namespace g = nyna::graphics;

class Graph {
public:
    // number of samples
    static const int DEPTH = 240;

    // size
    static const int WIDTH = DEPTH;
    static const int HEIGHT = 60;

    static const int VERTICAL_LINE_STEP = WIDTH / 8;

    // position
    const int left, top;
    
    // minimum vertical range
    const float min_range;

    float min_log[DEPTH];
    float max_log[DEPTH];
    float latest_value = 0;
    int num_data = 0;

    float total_min = 0;
    float total_max = 0;
    int total_min_idx = -1;
    int total_max_idx = -1;

    float horizontal_line_step = 1;

    Graph(int x, int y, float min_range) : 
        left(x), top(y), min_range(min_range)
    { }

    void push(float value, bool shift) {
        latest_value = value;

        if (num_data == 0) {
            num_data = 1;
            min_log[0] = value;
            max_log[0] = value;
        }
        else if (shift) {
            for (int i = DEPTH - 1; i >= 1; i--) {
                min_log[i] = min_log[i-1];
                max_log[i] = max_log[i-1];
            }
            min_log[0] = value;
            max_log[0] = value;
            if (num_data < DEPTH) {
                num_data += 1;
            }
        }
        else {
            if (min_log[0] > value) min_log[0] = value;
            if (max_log[0] < value) max_log[0] = value;
        }
        
        if (num_data == 0) {
            total_min = 0;
            total_max = 0;
            total_min_idx = -1;
            total_max_idx = -1;
        }
        else {
            total_min = min_log[0];
            total_max = max_log[0];
            total_min_idx = 0;
            total_max_idx = 0;
            for (int i = 1; i < num_data; i++) {
                if (min_log[i] < total_min) {
                    total_min = min_log[i];
                    total_min_idx = i;
                }
                if (max_log[i] > total_max) {
                    total_max = max_log[i];
                    total_max_idx = i;
                }
            }
        }
    }

    void render(g::Bitmap1bpp &dest) {
        if (num_data <= 0) return;

        int x_plot = left + WIDTH - 1;
        float total_center = (total_min + total_max) / 2;
        float y_range = total_max - total_min;
        if (y_range < min_range) y_range = min_range;
        float y_zoom = HEIGHT / y_range;

        int y_offset = top + HEIGHT / 2 + total_center * y_zoom;
        for (int i = 0; i < num_data; i++) {
            int y_top = y_offset - max_log[i] * y_zoom;
            int y_bottom = y_offset - min_log[i] * y_zoom;

            dest.fillRect(x_plot, y_top, 1, y_bottom - y_top + 2, g::BLACK);
            dest.fillRect(x_plot, y_bottom, 1, top + HEIGHT - y_bottom, g::BLACK, g::PixelOp::SRC_PATTERN);

            x_plot -= 1;
        }

        float level_top = (y_offset - top) / y_zoom;
        float level_bottom = (y_offset - (top + HEIGHT)) / y_zoom;
        float y_scale = level_top - level_bottom;

        // step of horizontal lines
        if (y_scale > 1000) horizontal_line_step = 500;
        else if (y_scale > 500) horizontal_line_step = 200;
        else if (y_scale > 200) horizontal_line_step = 100;
        else if (y_scale > 100) horizontal_line_step = 50;
        else if (y_scale > 50) horizontal_line_step = 20;
        else if (y_scale > 20) horizontal_line_step = 10;
        else if (y_scale > 10) horizontal_line_step = 5;
        else if (y_scale > 5) horizontal_line_step = 2;
        else if (y_scale > 2) horizontal_line_step = 1;
        else if (y_scale > 1) horizontal_line_step = 0.5f;
        else horizontal_line_step = 0.2f;
        
        g::Pen dotted = g::DEFAULT_PEN;
        dotted.dotPeriod = 3;
        dotted.dotPattern = 1;

        // draw horizontal lines
        float level = horizontal_line_step * ceilf(level_bottom / horizontal_line_step);
        while (level < level_top) {
            int y_line = y_offset - level * y_zoom;
            dest.drawLine(left, y_line, left + WIDTH, y_line, g::BLACK, dotted);
            level += horizontal_line_step;
        }

        // draw vertical lines
        for (int x_line = left + WIDTH - 1; x_line > left; x_line -= VERTICAL_LINE_STEP) {
            dest.drawLine(x_line, top, x_line, top + HEIGHT, g::BLACK, dotted);
        }

        // Min marker
        if (total_min_idx >= 0) {
            int x = left + WIDTH - total_min_idx - images::marker_down_mask.width / 2 - 1;
            int y = (y_offset - min_log[total_min_idx] * y_zoom) - images::marker_down_mask.height;
            dest.drawBitmap(x, y, images::marker_down_mask, g::PixelOp::GATE_OR);
            dest.drawBitmap(x + 1, y + 1, images::marker_down, g::PixelOp::GATE_AND);
        }

        // Max marker
        if (total_max_idx >= 0) {
            int x = left + WIDTH - total_max_idx - images::marker_up_mask.width / 2 - 1;
            int y = (y_offset - max_log[total_max_idx] * y_zoom);
            dest.drawBitmap(x, y, images::marker_up_mask, g::PixelOp::GATE_AND);
            dest.drawBitmap(x + 1, y + 1, images::marker_up, g::PixelOp::GATE_OR);
        }

        // Latest value marker        
        if (num_data > 0) {
            int x = left + WIDTH;
            int y = y_offset - latest_value * y_zoom - images::marker_left_mask.height / 2 - 1;
            dest.drawBitmap(x, y, images::marker_left_mask, g::PixelOp::GATE_OR);
            dest.drawBitmap(x + 1, y + 1, images::marker_left, g::PixelOp::GATE_AND);
        }
    }

};

}
