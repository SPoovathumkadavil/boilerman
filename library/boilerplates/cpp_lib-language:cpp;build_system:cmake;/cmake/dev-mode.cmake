include(cmake/folders.cmake)
include(CTest)

if(BUILD_TESTING AND EXISTS "${PROJECT_SOURCE_DIR}/test/CMakeLists.txt")
  add_subdirectory(test)
endif()

add_folders(Project)
