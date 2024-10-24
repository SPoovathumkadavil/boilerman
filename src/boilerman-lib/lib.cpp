
#include "lib.hpp"
#include "fileutil.hpp"

#ifndef IS_TESTING
#define IS_TESTING false
#endif

library::library()
    : _name {"boilerman"}
    , _test {IS_TESTING},
    _feta_dir {feta::directories(_name, feta::directories::get_home_dir() / ".loc.json", _test)}
{
  project_directories = _feta_dir.proj_dirs();
}

std::vector<Boiler> library::populate_boilers()
{
  std::vector<std::filesystem::path> b_dirs =
      get_dirs_in_dir(project_directories.lib);
  std::vector<Boiler> boilers;
  for (std::filesystem::path d : b_dirs)
  {
    boilers.push_back(Boiler(d));
  }
  return boilers;
}
