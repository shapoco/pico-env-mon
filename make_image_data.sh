#!/bin/bash

echo '#include "msb1stimage.hpp"' > images.cpp

./make_image_data.py    ./img/digit16.png   img_digit16 >> ./src/images.cpp
./make_image_data.py    ./img/digit32.png   img_digit32 >> ./src/images.cpp

./make_image_data.py    ./img/degc.png      img_degc    >> ./src/images.cpp
./make_image_data.py    ./img/percent.png   img_percent >> ./src/images.cpp
./make_image_data.py    ./img/hpa.png       img_hpa     >> ./src/images.cpp
./make_image_data.py    ./img/ppm.png       img_ppm     >> ./src/images.cpp

./make_image_data.py    ./img/step.png      img_step    >> ./src/images.cpp
