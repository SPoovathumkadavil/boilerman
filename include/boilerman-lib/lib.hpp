#pragma once

#include <vector>
#include <string>
#include <fetalib/directories.hpp>

#include "boiler.hpp"

/**
 * @brief The core implementation of the executable
 *
 * This class makes up the library part of the executable, which means that the
 * main logic is implemented here. This kind of separation makes it easy to
 * test the implementation for the executable, because the logic is nicely
 * separated from the command-line logic implemented in the main function.
 */
struct library
{
  /**
   * @brief Simply initializes the name member to the name of the project
   */
  library();

  std::vector<Boiler> populate_boilers();

  std::string _name;
  bool _test;
  feta::directories _feta_dir;
  feta::_proj_dirs project_directories;
};
