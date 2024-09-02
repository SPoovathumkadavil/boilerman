cmake_minimum_required(VERSION 3.16)

project(1Tests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

enable_testing()

# ---- Tests ----

file(GLOB_RECURSE 1_test_sources "src/*.cpp")
add_executable(1_test ${1_test_sources})
target_link_libraries(1_test 
  PRIVATE
  GTest::gtest_main
  1::1)
target_compile_features(1_test PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(1_test)

# ---- End-of-file commands ----

add_folders(Test)
