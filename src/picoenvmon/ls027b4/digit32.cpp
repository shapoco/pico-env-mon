#include "stdint.h"
#include "msb1stimage.hpp"
#include "images.hpp"
#include "digit32.hpp"

int digit32_draw_char(Msb1stImage &dest, int dx, int dy, char c, PixelOp op) {
    int w, h = 32;
    int sx = -1;
    if ('0' <= c && c <= '9') {
        w = 20;
        sx = w * (c - '0');
    }
    else if (c == ' ') {
        w = 20;
        // white space
    }
    else if (c == '-') {
        w = 12;
        sx = 208;
    }
    else {
        w = 8;
        sx = 200;
    }

    if (sx >= 0 && op != PixelOp::NOP) {
        dest.draw_image(img_digit32, dx, dy, w, h, sx, 0, op);
    }
    return w;
}

int digit32_draw_string(Msb1stImage &dest, int x, int y, const char *s, PixelOp op) {
    const char *ptr = s;
    if (!*ptr) return x;
    char c;
    while ((c = *(ptr++))) {
        x += digit32_draw_char(dest, x, y, c, op) + DIGIT32_GAP;
    }
    return x;
}

int digit32_measure_width(const char *s) {
    Msb1stImage *dummy = nullptr;
    return digit32_draw_string(*dummy, 0, 0, s, PixelOp::NOP);
}
