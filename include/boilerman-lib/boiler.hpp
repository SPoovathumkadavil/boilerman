#pragma once

#include <filesystem>
#include <string>

class Boiler
{
public:
  std::string _name;
  std::string _desc;
  std::string _type;
  std::string _lang;
  std::string _path;
  Boiler(std::string dir_path);
  ~Boiler() {};
  void use(std::filesystem::path output_path, std::string resolve_name);
};