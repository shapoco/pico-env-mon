#ifndef MSB1STIMAGE_HPP
#define MSB1STIMAGE_HPP

#include "stdint.h"

class Msb1stImage {
public:
    const int width;
    const int height;
    const int stride;
    uint8_t *data;

    Msb1stImage(int w, int h, uint8_t *data) :
        width(w), height(h), stride((w + 7) / 8), data(data)
    { }

    Msb1stImage(uint8_t *data) :
        width((int)data[0] + ((int)data[1] << 8)), 
        height((int)data[2] + ((int)data[3] << 8)), 
        stride((width + 7) / 8), 
        data(data + 4)
    { }

    static void clip_copy_rect(int sw, int sh, int dw, int dh, int *sl, int *st, int *dl, int *dt, int *w, int *h) {
        // s: source, d: destination
        // w: width, h: height
        // l: left, t: top, r: right, b: bottom
        if (*sl < 0) { *dl += *sl; *w += *sl; *sl = 0; }
        if (*st < 0) { *dl += *sl; *h += *st; *st = 0; }
        if (*dl < 0) { *sl += *dl; *w += *dl; *dl = 0; }
        if (*dt < 0) { *sl += *dl; *h += *dt; *dt = 0; }
        int sr = *sl + *w;
        int sb = *st + *h;
        int dr = *dl + *w;
        int db = *dt + *h;
        if (sr > sw) { *w -= (sr-sw); dr -= (sr-sw); }
        if (sb > sh) { *h -= (sb-sh); db -= (sb-sh); }
        if (dr > dw) { *w -= (dr-dw); }
        if (db > dh) { *h -= (db-dh); }
    }

    static void clip_fill_rect(int dw, int dh, int *dl, int *dt, int *w, int *h) {
        int sl = 0, st = 0; // dummy
        clip_copy_rect(dw, dh, dw, dh, &sl, &st, dl, dt, w, h);
    }

    void set_pixel(int x, int y, uint8_t color) {
        if (x < 0 || x >= width || y < 0 || y >= height) return;

        int i = y * stride + (x / 8);
        uint8_t mask = 1 << (~x & 0x7);
        if (color) {
            data[i] |= mask;
        }
        else {
            data[i] &= ~mask;
        }
    }

    uint8_t get_pixel(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) return 0;

        int i = y * stride + (x / 8);
        uint8_t mask = 1 << (~x & 0x7);
        return data[i] & mask ? 1 : 0;
    }

    void invert_pixel(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) return;

        int i = y * stride + (x / 8);
        uint8_t mask = 1 << (~x & 0x7);
        data[i] ^= mask;
    }

    void fill_rect(int x0, int y0, int w, int h, uint8_t color) {
        clip_fill_rect(width, height, &x0, &y0, &w, &h);
        int x1 = x0 + w;
        int y1 = y0 + h;
        for (int y = y0; y < y1; y++) {
            for (int x = x0; x < x1; x++) {
                set_pixel(x, y, color);
            }
        }
    }

    void fill_rect_with_pattern(int x0, int y0, int w, int h) {
        clip_fill_rect(width, height, &x0, &y0, &w, &h);
        int x1 = x0 + w;
        int y1 = y0 + h;
        for (int y = y0; y < y1; y++) {
            for (int x = x0; x < x1; x++) {
                set_pixel(x, y, (x + y) & 1);
            }
        }
    }

    void draw_horizontal_dotted_line(int x0, int y0, int w) {
        int h = 1;
        clip_fill_rect(width, height, &x0, &y0, &w, &h);
        if (h < 1) return;
        int x1 = x0 + w;
        for (int x = x0; x < x1; x += 3) {
            invert_pixel(x, y0);
        }
    }

    void draw_vertical_dotted_line(int x0, int y0, int h) {
        int w = 1;
        clip_fill_rect(width, height, &x0, &y0, &w, &h);
        if (w < 1) return;
        int y1 = y0 + h;
        for (int y = y0; y < y1; y += 3) {
            invert_pixel(x0, y);
        }
    }

    void clear(uint8_t color) {
        uint8_t value = color ? 0xff : 0x00;
        for (int i = 0; i < stride * height; i++) {
            data[i] = value;
        }
    }

    void draw_image(Msb1stImage &src, int dx0, int dy0, int w, int h, int sx0, int sy0) {
        clip_copy_rect(src.width, src.height, width, height, &sx0, &sy0, &dx0, &dy0, &w, &h);
        int sx1 = sx0 + w;
        int sy1 = sy0 + h;

        int dy = dy0;
        for (int sy = sy0; sy < sy1; sy++) {
            int dx = dx0;
            for (int sx = sx0; sx < sx1; sx++) {
                set_pixel(dx, dy, src.get_pixel(sx, sy));
                dx += 1;
            }
            dy += 1;
        }
    }

    void draw_image(Msb1stImage &src, int dx, int dy) {
        draw_image(src, dx, dy, src.width, src.height, 0, 0);
    }
    
};

#endif
