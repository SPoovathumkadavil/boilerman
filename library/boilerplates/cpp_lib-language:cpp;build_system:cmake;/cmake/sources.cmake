file(GLOB_RECURSE |||cpp_name|||_sources CONFIGURE_DEPENDS "src/|||cpp_name|||/*.cpp")

add_library(|||target_name||| ${|||cpp_name|||_sources})
add_library(|||target_name|||::|||target_name||| ALIAS |||target_name|||)

target_compile_features(|||target_name||| PUBLIC cxx_std_17)

target_include_directories(
  |||target_name||| ${warning_guard}
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
