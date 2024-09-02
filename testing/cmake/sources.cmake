
# ---- declare library ----

file(GLOB_RECURSE meow_lib_sources CONFIGURE_DEPENDS "src/meow-lib/*.cpp")

add_library(
    meow_lib OBJECT
    ${meow_lib_sources}
)

target_include_directories(
    meow_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/meow-lib>"
)

target_compile_features(meow_lib PUBLIC cxx_std_17)

# ---- declare executable ----

file(GLOB_RECURSE meow_sources CONFIGURE_DEPENDS "src/meow/*.cpp")

add_executable(meow_exe ${meow_sources})
add_executable(meow::exe ALIAS meow_exe)

set_property(TARGET meow_exe PROPERTY OUTPUT_NAME meow)

target_compile_features(meow_exe PRIVATE cxx_std_17)

target_link_libraries(meow_exe PRIVATE meow_lib)

target_include_directories(
    meow_exe ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/meow>"
)

# ---- add external libraries ----

include(cmake/external-lib.cmake)