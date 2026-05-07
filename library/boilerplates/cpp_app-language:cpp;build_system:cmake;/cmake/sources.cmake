file(GLOB_RECURSE |||cpp_name|||_lib_sources CONFIGURE_DEPENDS "src/|||cpp_name|||/*.cpp")
list(FILTER |||cpp_name|||_lib_sources EXCLUDE REGEX "/main\\.cpp$")

add_library(|||target_name|||_lib ${|||cpp_name|||_lib_sources})
target_compile_features(|||target_name|||_lib PUBLIC cxx_std_17)
target_include_directories(
    |||target_name|||_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

add_executable(|||target_name|||_exe "src/|||cpp_name|||/main.cpp")
add_executable(|||target_name|||::exe ALIAS |||target_name|||_exe)

set_property(TARGET |||target_name|||_exe PROPERTY OUTPUT_NAME |||target_name|||)
target_compile_features(|||target_name|||_exe PRIVATE cxx_std_17)
target_link_libraries(|||target_name|||_exe PRIVATE |||target_name|||_lib)
