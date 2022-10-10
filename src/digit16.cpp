#include "stdint.h"
#include "msb1stimage.hpp"
#include "images.hpp"

int digit16_draw_char(Msb1stImage &dest, int x, int y, char c) {
    int w, h = 16;
    if ('0' <= c && c <= '9') {
        w = 10;
        dest.draw_image(img_digit16, x, y, w, h, w * (c - '0'), 0);
    }
    else if (c == ' ') {
        w = 6;
        // white space
    }
    else if (c == '-') {
        w = 6;
        dest.draw_image(img_digit16, x, y, w, h, 104, 0);
    }
    else if (c == '/') {
        w = 6;
        dest.draw_image(img_digit16, x, y, w, h, 110, 0);
    }
    else {
        w = 4;
        dest.draw_image(img_digit16, x, y, w, h, 100, 0);
    }
    return w;
}

int digit16_draw_string(Msb1stImage &dest, int x, int y, const char *s) {
    const char *ptr = s;
    char c;
    while ((c = *(ptr++))) {
        x += digit16_draw_char(dest, x, y, c);
        x += 2;
    }
    return x;
}
