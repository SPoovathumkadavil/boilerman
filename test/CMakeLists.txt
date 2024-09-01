# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

cmake_minimum_required(VERSION 3.16)

project(boilermanTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Tests ----

enable_testing()

file(GLOB_RECURSE boilerman_test_sources "src/*.cpp")
add_executable(boilerman_test ${boilerman_test_sources})
target_link_libraries(boilerman_test 
  PRIVATE
  GTest::gtest_main
  boilerman_lib)
target_compile_features(boilerman_test PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(boilerman_test)

# ---- End-of-file commands ----

add_folders(Test)
