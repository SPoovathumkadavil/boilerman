# ---- Declare library ----

file(GLOB_RECURSE 1_1_sources CONFIGURE_DEPENDS "src/1/*.cpp")
add_library(
    1_1
    ${1_1_sources}
)
add_library(1::1 ALIAS 1_1)

include(GenerateExportHeader)
generate_export_header(
    1_1
    BASE_NAME 1
    EXPORT_FILE_NAME export/1/1_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(1_1 PUBLIC 1_STATIC_DEFINE)
endif()

set_target_properties(
    1_1 PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME 1
    OUTPUT_NAME 1
)

target_include_directories(
    1_1 ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    1_1 SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(1_1 PUBLIC cxx_std_17)

# ---- external libs ----

include(cmake/external-lib.cmake)
