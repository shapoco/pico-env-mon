#!/usr/bin/env python3

from PIL import Image

import sys
import numpy as np

arg_input_image = sys.argv[1]
arg_array_name = sys.argv[2]

img = Image.open(arg_input_image)
width, height = img.size
img_pixels = np.array([[img.getpixel((x,y)) for x in range(width)] for y in range(height)])

print()
print('const uint8_t %s_data[] = {' % arg_array_name)
print('    %d, %d, %d, %d,' % (width % 256, width // 256, height % 256, height // 256))

index = 0
stride = (width + 7) // 8
length = stride * height

for y in range(height):
    for x_step in range(stride):
        byte = 0
        for x_sub in range(8):
            x = x_step * 8 + x_sub
            if x < width:
                pixel = img_pixels[y, x]
                if pixel[0] != 0:
                    byte |= 1 << (7 - x_sub)
        if (index % 16 == 0):
            print('    ', end='')
        print('0x%02x, ' % byte, end='')
        if (index % 16 == 15) or (index == length - 1):
            print()
        index += 1

print('};')
print()
print('Msb1stImage %s((uint8_t*)%s_data);' % (arg_array_name, arg_array_name))
