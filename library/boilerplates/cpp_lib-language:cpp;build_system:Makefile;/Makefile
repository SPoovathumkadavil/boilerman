LIB_NAME = |||target_name|||

GLOBAL_LIB_DIR = $(HOME)/.local/lib
GLOBAL_INC_DIR = $(HOME)/.local/include
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = build
INC_DIR = include
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_SRC_FILES = $(shell find $(TEST_DIR) -type f -name "*.cpp" 2>/dev/null)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/$(TEST_DIR)/%.o, $(TEST_SRC_FILES))
TARGET = $(OBJ_DIR)/lib$(LIB_NAME).a
TEST_TARGET = $(OBJ_DIR)/test_$(LIB_NAME)

CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -fPIC -I$(INC_DIR)
AR ?= ar
ARFLAGS = rcs
DEPFLAGS = -MMD -MP
LDFLAGS ?=

.PHONY: build clean compile_db debug install release test uninstall

build: $(TARGET)

debug: CXXFLAGS += -O0 -g
debug: clean build

release: CXXFLAGS += -O2 -DNDEBUG
release: clean build

compile_db:
	$(MAKE) clean
	bear -- $(MAKE) build

test: $(TEST_TARGET)
	$(TEST_TARGET)

install: build
	mkdir -p $(GLOBAL_LIB_DIR)
	mkdir -p $(GLOBAL_INC_DIR)
	cp $(TARGET) $(GLOBAL_LIB_DIR)
	cp -r $(INC_DIR)/* $(GLOBAL_INC_DIR)

uninstall:
	rm -f $(GLOBAL_LIB_DIR)/lib$(LIB_NAME).a
	rm -f $(GLOBAL_INC_DIR)/|||cpp_name|||.hpp

$(TARGET): $(OBJ_FILES)
	mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $(OBJ_FILES)

$(TEST_TARGET): $(TARGET) $(TEST_OBJ_FILES)
	mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $@ $(TEST_OBJ_FILES) $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

-include $(OBJ_FILES:.o=.d)
-include $(TEST_OBJ_FILES:.o=.d)
