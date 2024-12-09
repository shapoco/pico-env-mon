#include "stdint.h"
#include "msb1stimage.hpp"
#include "images.hpp"

int digit16_draw_char(Msb1stImage &dest, int x, int y, char c, PixelOp op) {
    int w, h = 16;
    if ('0' <= c && c <= '9') {
        w = 9;
        dest.draw_image(img_digit16, x, y, w, h, w * (c - '0'), 0, op);
    }
    else if (c == ' ') {
        w = 6;
        // white space
    }
    else if (c == '-') {
        w = 6;
        dest.draw_image(img_digit16, x, y, w, h, 94, 0, op);
    }
    else if (c == '/') {
        w = 10;
        dest.draw_image(img_digit16, x, y, w, h, 100, 0, op);
    }
    else if (c == 'v') {
        w = 9;
        dest.draw_image(img_digit16, x, y, w, h, 110, 0, op);
    }
    else {
        w = 4;
        dest.draw_image(img_digit16, x, y, w, h, 90, 0, op);
    }
    return w;
}

int digit16_draw_string(Msb1stImage &dest, int x, int y, const char *s, PixelOp op) {
    const char *ptr = s;
    char c;
    while ((c = *(ptr++))) {
        x += digit16_draw_char(dest, x, y, c, op);
        x += 2;
    }
    return x;
}
