
MAKEFLAGS += --silent

# Project directories, where the local project files are stored
DEP_DIR = dependencies
OBJ_DIR = obj
BIN_DIR = bin
CONFIG_DIR = config
SRC_DIR = src
INC_DIR = include

APP = "project"

# All compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -I$(INC_DIR) -g
C = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -I$(INC_DIR) -g
LD = g++
LDFLAGS = -L/usr/local/lib -I$(INC_DIR)
LDLIBS = -lm

# All compilable files
CPP_SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.cpp")
C_SRC_FILES += $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_SRC_FILES)) $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRC_FILES))

.PHONY: build
build: $(OBJ_FILES)
	echo "linking objects..."
	$(LD) $(LDFLAGS) $(OBJ_FILES) -o $(BIN_DIR)/$(APP) $(LDLIBS)
	echo "done!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(C) $(CFLAGS) -c $< -o $@

# Run the compiled binary
.PHONY: run
run:
	./$(BIN_DIR)/$(APP)

# Clean all object files
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/*

# Clean all object files and the binary
.PHONY: cleanall
cleanall:
	rm -rf $(OBJ_DIR)/*
	rm -f $(BIN_DIR)/$(APP)
	
# PATH directories, where system wide binaries are stored
HOME_DIR = /Users/$(USER)
PATH_BIN_DIR = $(HOME_DIR)/Documents/dev/.bin
P_PATH_DEP_DIR = $(HOME_DIR)/Documents/dev/.dependencies/$(APP)
P_PATH_CONFIG_DIR = $(HOME_DIR)/Documents/dev/.config/$(APP)

# Move all binaries to respective directories
.PHONY: install
install:
	echo "installing dependencies..."
	mkdir -p $(P_PATH_DEP_DIR)
	cp -r $(DEP_DIR)/* $(P_PATH_DEP_DIR) 2>/dev/null || :
	echo "installing binaries..."
	mkdir -p $(PATH_BIN_DIR)
	cp -r $(BIN_DIR)/* $(PATH_BIN_DIR) 2>/dev/null || :
	echo "installing config files..."
	mkdir -p $(P_PATH_CONFIG_DIR)
	cp -r $(CONFIG_DIR)/* $(P_PATH_CONFIG_DIR) 2>/dev/null || :
	echo "done!"

# Remove all project files from respective sys-wide directories
.PHONY: uninstall
uninstall:
	echo "uninstalling dependencies..."
	rm -rf $(P_PATH_DEP_DIR)
	echo "uninstalling config files..."
	rm -rf $(P_PATH_CONFIG_DIR)
	for file in $(BIN_DIR)/*; do \
		echo "uninstalling binary (if exists): $$file"; \
		rm -f $(PATH_BIN_DIR)/$$(basename $$file); \
	done
	echo "Done!"

.PHONY: help
help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  build       - Compile the project"
	@echo "  run         - Run the compiled binary"
	@echo "  clean       - Clean all object files"
	@echo "  cleanall    - Clean all object files and the binary"
	@echo "  init        - Initialize the project"
	@echo "  install     - Install the project"
	@echo "  uninstall   - Uninstall the project"
	@echo "  help        - Display this help message"
	@echo ""
	@echo "Variables:"
	@echo "  name        - Name of the project, set during initialization to change the project name"
	@echo ""
	@echo "Example:"
	@echo "  make init name=my_project"
	@echo "  make build"
	@echo "  make run"
	@echo "  make clean"
	@echo "  make cleanall"
	@echo "  make install"
	@echo "  make uninstall"
	@echo "  make help"
	@echo ""
