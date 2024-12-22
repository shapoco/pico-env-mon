.PHONY: all images fonts clean distclean

BOARD := pico

REPO_DIR = $(shell pwd)
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin/$(BOARD)

ifdef NYNA_PATH
NYNA_DIR = ${NYNA_PATH}
else
NYNA_DIR = nyna
endif

APP_NAME = pico_env_mon
BIN_NAME = $(APP_NAME).uf2
ELF_NAME = $(APP_NAME).elf
BIN = $(BIN_DIR)/$(BIN_NAME)
ELF = $(BIN_DIR)/$(ELF_NAME)

SRC_LIST = \
	$(shell find $(NYNA_DIR)/ -type f -name '*.hpp') \
	$(shell find $(NYNA_DIR)/ -type f -name '*.cpp') \
	$(shell find $(SRC_DIR)/ -type f -name '*.hpp') \
	$(shell find $(SRC_DIR)/ -type f -name '*.cpp')

IMAGE_SRC_GEN_CMD = $(NYNA_DIR)/bin/gen_bmp_array.py
FONT_SRC_GEN_CMD = $(NYNA_DIR)/bin/gen_font_array.py

IMAGES_BMP_DIR = bmp
IMAGES_OUT_DIR = $(SRC_DIR)/images
IMAGES_BMP_LIST = $(wildcard $(IMAGES_BMP_DIR)/*.png)
IMAGES_CPP_LIST = $(patsubst $(IMAGES_BMP_DIR)/%.png,$(IMAGES_OUT_DIR)/%.cpp,$(IMAGES_BMP_LIST))
IMAGES_HPP_LIST = $(patsubst $(IMAGES_BMP_DIR)/%.png,$(IMAGES_OUT_DIR)/%.hpp,$(IMAGES_BMP_LIST))

FONTS_BMP_DIR = fonts
FONTS_OUT_DIR = $(SRC_DIR)/fonts
FONTS_BMP_LIST = $(wildcard $(FONTS_BMP_DIR)/*.png)
FONTS_CPP_LIST = $(patsubst $(FONTS_BMP_DIR)/%.png,$(FONTS_OUT_DIR)/%.cpp,$(FONTS_BMP_LIST))
FONTS_HPP_LIST = $(patsubst $(FONTS_BMP_DIR)/%.png,$(FONTS_OUT_DIR)/%.hpp,$(FONTS_BMP_LIST))

EXTRA_DEPENDENCIES = \
	Makefile \
	CMakeLists.txt \
	$(IMAGE_SRC_GEN_CMD) \
	$(FONT_SRC_GEN_CMD)

all: $(BIN)

images: $(IMAGES_HPP_LIST)

fonts: $(FONTS_HPP_LIST)

$(IMAGES_OUT_DIR)/%.hpp: $(IMAGES_OUT_DIR)/%.cpp
	@echo -n ""

$(IMAGES_OUT_DIR)/%.cpp: $(IMAGES_BMP_DIR)/%.png $(EXTRA_DEPENDENCIES) $(IMAGE_SRC_GEN_CMD)
	@echo "Generating: '$@'"
	@mkdir -p $(IMAGES_OUT_DIR)
	@$(IMAGE_SRC_GEN_CMD) \
		--src $< \
		--name $(patsubst $(IMAGES_BMP_DIR)/%.png,%,$<) \
		--outdir $(IMAGES_OUT_DIR) \
		--out_namespace picoenvmon::images

$(FONTS_OUT_DIR)/%.hpp: $(FONTS_OUT_DIR)/%.cpp
	@echo -n ""

$(FONTS_OUT_DIR)/%.cpp: $(FONTS_BMP_DIR)/%.png $(EXTRA_DEPENDENCIES) $(FONT_SRC_GEN_CMD)
	@echo "Generating: '$@'"
	@mkdir -p $(FONTS_OUT_DIR)
	@$(FONT_SRC_GEN_CMD) \
		--src $< \
		--name $(patsubst $(FONTS_BMP_DIR)/%.png,%,$<) \
		--outdir $(FONTS_OUT_DIR) \
		--out_namespace picoenvmon::fonts \
		$(shell cat $(patsubst %.png,%.args.txt,$<))

$(BIN): $(SRC_LIST) $(IMAGES_HPP_LIST) $(FONTS_HPP_LIST) $(EXTRA_DEPENDENCIES)
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

objclean:
	rm -rf $(BUILD_DIR)/nyna
	rm -f $(BUILD_DIR)/*.uf2
	rm -f $(BUILD_DIR)/*.elf
	rm -f $(BUILD_DIR)/*.obj
	rm -f $(BUILD_DIR)/*.map
	rm -f $(BUILD_DIR)/*.ld

clean: objclean
	rm -rf $(BUILD_DIR)

distclean: clean
	rm -rf $(BIN_DIR)

