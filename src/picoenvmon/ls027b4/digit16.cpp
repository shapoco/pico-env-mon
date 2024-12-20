#include "stdint.h"
#include "msb1stimage.hpp"
#include "images.hpp"
#include "digit16.hpp"

int digit16_draw_char(Msb1stImage &dest, int dx, int dy, char c, PixelOp op) {
    int w, h = 16;
    int sx = -1;
    if ('0' <= c && c <= '9') {
        w = 9;
        sx = w * (c - '0');
    }
    else if (c == ' ') {
        w = 6;
        // white space
    }
    else if (c == '-') {
        w = 6;
        sx = 94;
    }
    else if (c == '/') {
        w = 10;
        sx = 100;
    }
    else if (c == 'v') {
        w = 9;
        sx = 110;
    }
    else {
        w = 4;
        sx = 90;
    }

    if (sx >= 0 && op != PixelOp::NOP) {
        dest.draw_image(img_digit16, dx, dy, w, h, sx, 0, op);
    }
    return w;
}

int digit16_draw_string(Msb1stImage &dest, int x, int y, const char *s, PixelOp op) {
    const char *ptr = s;
    if (!*ptr) return x;
    char c;
    while ((c = *(ptr++))) {
        x += digit16_draw_char(dest, x, y, c, op) + DIGIT16_GAP;
    }
    return x;
}

int digit16_measure_width(const char *s) {
    Msb1stImage *dummy = nullptr;
    return digit16_draw_string(*dummy, 0, 0, s, PixelOp::NOP);
}
