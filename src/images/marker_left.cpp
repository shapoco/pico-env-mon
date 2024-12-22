#include <stdint.h>

#include "nyna/graphics/bitmap1bpp.hpp"

namespace picoenvmon::images {

using namespace nyna::graphics;

static const uint8_t marker_left_data[] = {
    0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 
};

Bitmap1bpp marker_left(7, 13, 1, (uint8_t *)marker_left_data);

}
