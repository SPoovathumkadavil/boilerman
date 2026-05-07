# |||project_name|||

## Build

```sh
make build
```

## Test

```sh
make build-tests
ctest --test-dir build --output-on-failure
```

## Install

```sh
cmake --install build
```

The install rules export a CMake package, so consumers can use:

```cmake
find_package(|||target_name||| CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE |||target_name|||::|||target_name|||)
```
