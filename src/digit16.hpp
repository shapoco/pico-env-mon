#ifndef DIGIT16_HPP
#define DIGIT16_HPP

#include "msb1stimage.hpp"

int digit16_draw_char(Msb1stImage &dest, int x, int y, char c, PixelOp op = PixelOp::AND);
int digit16_draw_string(Msb1stImage &dest, int x, int y, const char *s, PixelOp op = PixelOp::AND);

#endif
