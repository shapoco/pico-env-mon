#ifndef DIGIT32_HPP
#define DIGIT32_HPP

#include "msb1stimage.hpp"

static constexpr int DIGIT32_GAP = 4;

int digit32_draw_char(Msb1stImage &dest, int x, int y, char c, PixelOp op = PixelOp::AND);
int digit32_draw_string(Msb1stImage &dest, int x, int y, const char *s, PixelOp op = PixelOp::AND);
int digit32_measure_width(const char *s);

#endif
