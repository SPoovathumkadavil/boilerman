#include "boilerman.hpp"

#include <exception>
#include <iostream>

int main() {
  try {
    return run_interactive_app();
  } catch (const std::exception &e) {
    std::cerr << "boilerman: " << e.what() << "\n";
    return 1;
  }
}
