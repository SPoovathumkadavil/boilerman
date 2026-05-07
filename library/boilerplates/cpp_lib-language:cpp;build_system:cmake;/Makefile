BUILD_DIR = build

.PHONY: build build-tests clean install

build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

build-tests:
	cmake -S . -B $(BUILD_DIR) -D |||cpp_name|||_DEVELOPER_MODE=ON
	cmake --build $(BUILD_DIR)

install:
	cmake --install $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
