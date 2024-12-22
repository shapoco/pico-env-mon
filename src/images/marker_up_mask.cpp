#include <stdint.h>

#include "nyna/graphics/bitmap1bpp.hpp"

namespace picoenvmon::images {

using namespace nyna::graphics;

static const uint8_t marker_up_mask_data[] = {
    0xef, 0x01, 0xc7, 0x01, 0xc7, 0x01, 0x83, 0x01, 0x83, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
    0x00, 0x00, 
};

Bitmap1bpp marker_up_mask(9, 9, 2, (uint8_t *)marker_up_mask_data);

}
