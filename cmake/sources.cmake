
# ---- declare library ----

file(GLOB_RECURSE boilerman_lib_sources CONFIGURE_DEPENDS "src/boilerman-lib/*.cpp")

add_library(
    boilerman_lib OBJECT
    ${boilerman_lib_sources}
)

target_include_directories(
    boilerman_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/boilerman-lib>"
)

target_compile_features(boilerman_lib PUBLIC cxx_std_17)

# ---- declare executable ----

file(GLOB_RECURSE boilerman_sources CONFIGURE_DEPENDS "src/boilerman/*.cpp")

add_executable(boilerman_exe ${boilerman_sources})
add_executable(boilerman::exe ALIAS boilerman_exe)

set_property(TARGET boilerman_exe PROPERTY OUTPUT_NAME boilerman)

target_compile_features(boilerman_exe PRIVATE cxx_std_17)

target_link_libraries(boilerman_exe PRIVATE boilerman_lib)

target_include_directories(
    boilerman_exe ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/boilerman>"
)

# ---- add external libraries ----

include(cmake/external-lib.cmake)
