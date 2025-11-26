

BUILD_DIR = build
TARGET = |||name|||

build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

build-tests:
	cmake -S . -B $(BUILD_DIR) -D |||name|||_DEVELOPER_MODE ON
	cmake --build $(BUILD_DIR)

run:
	$(BUILD_DIR)/$(TARGET)

