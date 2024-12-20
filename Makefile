.PHONY: all bmp clean distclean

BOARD := pico

REPO_DIR = $(shell pwd)
SRC_DIR = src
BMP_DIR = bmp
BUILD_DIR = build
BIN_DIR = bin/$(BOARD)

APP_NAME = pico_env_mon
BIN_NAME = $(APP_NAME).uf2
ELF_NAME = $(APP_NAME).elf
BIN = $(BIN_DIR)/$(BIN_NAME)
ELF = $(BIN_DIR)/$(ELF_NAME)

IMAGES_CPP = $(SRC_DIR)/picoenvmon/ls027b4/images.cpp

SRC_LIST = \
	$(wildcard $(SRC_DIR)/*.*) \
	$(wildcard $(SRC_DIR)/picoenvmon/*.*) \
	$(wildcard $(SRC_DIR)/picoenvmon/ls027b4/*.*)

EXTRA_DEPENDENCIES = \
	Makefile \
	CMakeLists.txt

all: $(BIN)

bmp: $(IMAGES_CPP)

$(IMAGES_CPP): $(wildcard $(BMP_DIR)/*.*) $(EXTRA_DEPENDENCIES)
	@echo '#include "picoenvmon/ls027b4/msb1stimage.hpp"' > ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/digit16.png           img_digit16         >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/digit32.png           img_digit32         >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/degc.png              img_degc            >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/percent.png           img_percent         >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/hpa.png               img_hpa             >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/ppm.png               img_ppm             >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/step.png              img_step            >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/marker_left.png       img_marker_left     >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/marker_down.png       img_marker_down     >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/marker_up.png         img_marker_up       >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/marker_left_mask.png  img_marker_left_mask>> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/marker_down_mask.png  img_marker_down_mask>> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/marker_up_mask.png    img_marker_up_mask  >> ./src/picoenvmon/ls027b4/images.cpp
	./make_image_data.py    ./bmp/logo.png              img_logo            >> ./src/picoenvmon/ls027b4/images.cpp

$(BIN): $(SRC_LIST) $(EXTRA_DEPENDENCIES)
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& cmake .. \
		&& make -j
	mkdir -p $(BIN_DIR)
	cp $(BUILD_DIR)/$(BIN_NAME) $(BIN)
	cp $(BUILD_DIR)/$(ELF_NAME) $(ELF)
	@echo "------------------------------"
	@echo -n "UF2 File: "
	@du -h $(BIN)
	@echo -n "ELF File: "
	@du -h $(ELF)

$(ELF): $(BIN)

ifneq ("$(wildcard debug.mk)", "")
include debug.mk
else ifneq ("$(shell which cmd.exe)", "")
include debug/wsl/debug.sample.mk
endif

clean:
	rm -rf build

distclean: clean
	rm -rf bin
	rm -f build/*.uf2
	rm -f build/*.elf

