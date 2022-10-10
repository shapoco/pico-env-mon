.PHONY: all install clean

REPO_DIR=$(shell pwd)
SRC_DIR=src
BUILD_DIR=build

BIN_NAME=pico_env_mon.uf2
BIN=$(BUILD_DIR)/$(BIN_NAME)

SRC_LIST=$(wildcard $(SRC_DIR)/*.*)

all: $(BIN)

$(BIN): $(SRC_LIST) CMakeLists.txt
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) \
		&& cmake .. \
		&& \make -j8
	@echo "------------------------------"
	@echo "UF2 File:"
	@echo $(REPO_DIR)/$(BIN)
	@ls -l $(REPO_DIR)/$(BIN)

install: $(BIN)
	sudo mkdir -p /mnt/e
	sudo mount -t drvfs e: /mnt/e
	cp $(BIN) /mnt/e/.

clean:
	rm -rf build
