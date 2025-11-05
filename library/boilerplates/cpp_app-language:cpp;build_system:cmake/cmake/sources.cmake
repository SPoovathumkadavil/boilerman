
# ---- declare executable ----

file(GLOB_RECURSE |||name|||_sources CONFIGURE_DEPENDS "src/|||name|||/*.cpp")

add_executable(|||name|||_exe ${|||name|||_sources})
add_executable(|||name|||::exe ALIAS |||name|||_exe)

set_property(TARGET |||name|||_exe PROPERTY OUTPUT_NAME |||name|||)

target_compile_features(|||name|||_exe PRIVATE cxx_std_17)

target_link_libraries(|||name|||_exe PRIVATE |||name|||_lib)

target_include_directories(
    |||name|||_exe ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/[[name]]>"
)

