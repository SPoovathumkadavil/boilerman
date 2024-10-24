
#include <fetalib/cli/colors.hpp>

#include "boiler.hpp"
#include "fileutil.hpp"

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
    std::printf(feta::colorize("path: %s does not exist.\n", feta::Color::RED).c_str(), dir_path.c_str());
  }
}

void Boiler::use(std::filesystem::path output_path, std::map<std::string, std::string> resolve_map) {
  std::printf(feta::colorize("using %s to create %s\n", feta::Color::BLUE).c_str(), _name.c_str(), resolve_map["name"].c_str());
  recursive_resolve_copy(_path, output_path, resolve_map);
  std::printf(feta::colorize("\n%s successfully initialized\n", feta::Color::CYAN).c_str(), resolve_map["name"].c_str());
}
