
APP_NAME = boilerman

GLOBAL_LIBRARY_DIR = $(HOME)/.local/library
INSTALL_DIR = $(HOME)/.local/bin
LIB_DIR = libs
LIBRARY_DIR = library
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = build
TARGET_DIR = $(OBJ_DIR)
INC_DIR = include
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
APP_OBJ_FILES = $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES))
TEST_SRC_FILES = $(shell find $(TEST_DIR) -type f -name "*.cpp" 2>/dev/null)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/$(TEST_DIR)/%.o, $(TEST_SRC_FILES))

LIBS := $(notdir $(wildcard $(LIB_DIR)/*))
LIBNAMES := $(patsubst lib%.so, %, $(LIBS))

CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -fPIC -I$(INC_DIR)
DEPFLAGS = -MMD -MP
LDFLAGS = # -L$(GLOBAL_LIB_DIR) -L$(LIB_DIR) $(addprefix -l,$(LIBNAMES))
TARGET = $(TARGET_DIR)/$(APP_NAME)
TEST_TARGET = $(TARGET_DIR)/test_$(APP_NAME)

.PHONY: build clean debug install release test uninstall

# Default target
build: $(TARGET)

release: CXXFLAGS += -O2 -DNDEBUG
release: clean build

debug: CXXFLAGS += -O0 -g
debug: clean build

install: build
	rm -f $(INSTALL_DIR)/$(notdir $(TARGET))
	rm -rf $(GLOBAL_LIBRARY_DIR)/$(APP_NAME)
	mkdir -p $(GLOBAL_LIBRARY_DIR)
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)
	cp -r $(LIBRARY_DIR) $(GLOBAL_LIBRARY_DIR)/$(APP_NAME)

uninstall:
	rm -f $(INSTALL_DIR)/$(notdir $(TARGET))
	rm -rf $(GLOBAL_LIBRARY_DIR)/$(APP_NAME)

# Rule to build the app
$(TARGET): $(OBJ_FILES)
	mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ_FILES)

$(TEST_TARGET): $(APP_OBJ_FILES) $(TEST_OBJ_FILES)
	mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $@ $(APP_OBJ_FILES) $(TEST_OBJ_FILES)

test: $(TEST_TARGET)
	$(TEST_TARGET)

# Rule to compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR)

-include $(OBJ_FILES:.o=.d)
-include $(TEST_OBJ_FILES:.o=.d)
