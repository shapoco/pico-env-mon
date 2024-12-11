#ifndef DIGIT16_HPP
#define DIGIT16_HPP

#include "msb1stimage.hpp"

static constexpr int DIGIT16_GAP = 2;

int digit16_draw_char(Msb1stImage &dest, int x, int y, char c, PixelOp op = PixelOp::AND);
int digit16_draw_string(Msb1stImage &dest, int x, int y, const char *s, PixelOp op = PixelOp::AND);
int digit16_measure_width(const char *s);

#endif
