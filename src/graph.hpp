#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "stdint.h"
#include "math.h"
#include "msb1stimage.hpp"

class Graph {
public:
    static const int DEPTH = 240;
    static const int WIDTH = DEPTH;
    static const int HEIGHT = 60;
    static const int VERTICAL_LINE_STEP = WIDTH / 8;
    const int left, top;
    const float min_scale;
    float min_log[DEPTH];
    float max_log[DEPTH];
    int num_data = 0;
    float total_min = 0;
    float total_max = 0;
    float y_step = 1;

    Graph(int x, int y, float min_scale) : 
        left(x), top(y), min_scale(min_scale)
    { }

    void push(float value, bool shift) {
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
        }
        else {
            total_min = min_log[0];
            total_max = max_log[0];
            for (int i = 1; i < num_data; i++) {
                if (min_log[i] < total_min) total_min =  min_log[i];
                if (max_log[i] > total_max) total_max =  max_log[i];
            }
        }
        
    }

    void draw(Msb1stImage &dest) {
        if (num_data <= 0) return;

        int x_plot = left + WIDTH - 1;
        float total_center = (total_min + total_max) / 2;
        float y_range = total_max - total_min;
        if (y_range < min_scale) y_range = min_scale;
        float y_zoom = HEIGHT / y_range;

        int y_offset = top + HEIGHT / 2 + total_center * y_zoom;
        int last_y_top, last_y_bottom; 
        for (int i = 0; i < num_data; i++) {
            int y_top = y_offset - max_log[i] * y_zoom;
            int y_bottom = y_offset - min_log[i] * y_zoom;

            // 変化量が大きいときに線が途切れないように前の点と繋げる
            if (i > 0 && y_top > last_y_bottom) y_top = last_y_bottom;
            if (i > 0 && y_bottom < last_y_top) y_bottom = last_y_top;
            
            dest.fill_rect(x_plot, y_top - 1, 1, y_bottom - y_top + 2, 0);
            x_plot -= 1;
            last_y_top = y_top;
            last_y_bottom = y_bottom;
        }

        float level_top = (y_offset - top) / y_zoom;
        float level_bottom = (y_offset - (top + HEIGHT)) / y_zoom;
        float y_scale = level_top - level_bottom;

        // step of horizontal lines
        if (y_scale > 1000) y_step = 500;
        else if (y_scale > 500) y_step = 200;
        else if (y_scale > 200) y_step = 100;
        else if (y_scale > 100) y_step = 50;
        else if (y_scale > 50) y_step = 20;
        else if (y_scale > 20) y_step = 10;
        else if (y_scale > 10) y_step = 5;
        else if (y_scale > 5) y_step = 2;
        else if (y_scale > 2) y_step = 1;
        else if (y_scale > 1) y_step = 0.5f;
        else y_step = 0.2f;
        
        // draw horizontal lines
        float level = y_step * ceilf(level_bottom / y_step);
        while (level < level_top) {
            int y_line = y_offset - level * y_zoom;
            dest.draw_horizontal_dotted_line(left, y_line, WIDTH, 0);
            level += y_step;
        }

        // draw vertical lines
        for (int x_line = left + WIDTH - 1; x_line > left; x_line -= VERTICAL_LINE_STEP) {
            dest.draw_vertical_dotted_line(x_line, top, HEIGHT, 0);
        }
    }
};

#endif
