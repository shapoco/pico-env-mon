#include <stdint.h>

#include "nyna/graphics/bitmap1bpp.hpp"

namespace picoenvmon::images {

using namespace nyna::graphics;

static const uint8_t marker_up_data[] = {
    0x08, 0x08, 0x1c, 0x1c, 0x3e, 0x3e, 0x7f, 
};

Bitmap1bpp marker_up(7, 7, 1, (uint8_t *)marker_up_data);

}
