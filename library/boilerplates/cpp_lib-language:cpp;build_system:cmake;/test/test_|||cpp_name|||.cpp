#include "|||cpp_name|||/|||cpp_name|||.hpp"

#include <iostream>
#include <stdexcept>

void require(bool condition, const char *message) {
  if (!condition) {
    throw std::runtime_error(message);
  }
}

int main() {
  try {
    require(|||cpp_name|||::version() == 1, "version should be 1");
  } catch (const std::exception &e) {
    std::cerr << "test failed: " << e.what() << "\n";
    return 1;
  }

  std::cout << "All tests passed.\n";
  return 0;
}
