
#include "boiler.hpp"
#include "fileutil.hpp"
#include <fmt/color.h>

Boiler::Boiler(std::string dir_path)
    : _path {dir_path}
{
  if (std::filesystem::exists(dir_path)) {
    _name = _path.substr(_path.find_last_of("/\\") + 1);
    _lang =
        _name.substr(_name.find_first_of("_") + 1,
                     _name.find_last_of(".") - _name.find_first_of("_") - 1);
    _desc = _name.substr(0, _name.find_first_of("_"));
    _type = _name.substr(_name.find_last_of(".") + 1);
  } else {
    fmt::print(fg(fmt::color::red), "path: {} does not exist.\n", dir_path);
  }
}

void Boiler::use(std::filesystem::path output_path, std::string resolve_name) {
  fmt::print(fg(fmt::color::cyan), "using {} to create {}\n", _name, resolve_name);
  recursive_resolve_copy(_path, output_path, resolve_name);
  fmt::print(fg(fmt::color::green), "\n{} successfully initialized\n", resolve_name);
}
