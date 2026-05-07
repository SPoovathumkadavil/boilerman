add_executable(|||target_name|||_test test_|||cpp_name|||.cpp)
target_link_libraries(|||target_name|||_test PRIVATE |||target_name|||)

add_test(NAME |||target_name|||_test COMMAND |||target_name|||_test)
