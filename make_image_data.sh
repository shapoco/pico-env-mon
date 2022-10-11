#!/bin/bash

echo '#include "msb1stimage.hpp"' > ./src/images.cpp

./make_image_data.py    ./bmp/digit16.png   img_digit16 >> ./src/images.cpp
./make_image_data.py    ./bmp/digit32.png   img_digit32 >> ./src/images.cpp

./make_image_data.py    ./bmp/degc.png      img_degc    >> ./src/images.cpp
./make_image_data.py    ./bmp/percent.png   img_percent >> ./src/images.cpp
./make_image_data.py    ./bmp/hpa.png       img_hpa     >> ./src/images.cpp
./make_image_data.py    ./bmp/ppm.png       img_ppm     >> ./src/images.cpp

./make_image_data.py    ./bmp/step.png      img_step    >> ./src/images.cpp
