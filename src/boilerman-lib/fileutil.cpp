
#include <fstream>
#include <sstream>
#include <algorithm>
#include <fetalib/cli/colors.hpp>

#include "fileutil.hpp"

std::string resolve_string(std::string str,
                           std::map<std::string, std::string> resolve_map)
{
  for (std::map<std::string, std::string>::iterator pair = resolve_map.begin();
       pair != resolve_map.end();
       ++pair)
  {
    std::string key = pair->first;
    std::string search_key = "[[" + key + "]]";
    std::string cap_search_key = "[%C[" + key + "]%C]";
    std::string val = pair->second;
    std::string cap_val = val;
    std::transform(cap_val.begin(), cap_val.end(), cap_val.begin(), ::toupper);
    while (str.find(search_key) != std::string::npos)
      str.replace(str.find(search_key), search_key.length(), val);
    while (str.find(cap_search_key) != std::string::npos)
      str.replace(str.find(cap_search_key), cap_search_key.length(), cap_val);
  }
  return str;
}

void recursive_resolve(std::filesystem::path dir_path,
                       std::map<std::string, std::string> resolve_map)
{
  std::printf(feta::colorize("resolving files to %s\n", feta::Color::BLUE).c_str(), dir_path.c_str());
  
  if (std::filesystem::is_directory(dir_path)) {
    for (const auto& dir_entry :
         std::filesystem::recursive_directory_iterator(dir_path))
    {
      std::string path_name = dir_entry.path();

      // entry resolver
      path_name = resolve_string(path_name, resolve_map);

      std::printf(feta::colorize("resolving %s --> %s\n", feta::Color::BLUE).c_str(), dir_entry.path().filename().c_str(), path_name.c_str());

      // if file
      if (dir_entry.is_regular_file()) {
        std::ostringstream text;
        std::ifstream in_file(dir_entry.path());
        text << in_file.rdbuf();
        std::string str = text.str();

        // in-file name search
        str = resolve_string(str, resolve_map);

        in_file.close();

        std::filesystem::create_directories(
            std::filesystem::path(path_name).parent_path());

        std::ofstream out_file(path_name);
        out_file << str;
      } else if (!dir_entry.is_directory()) {
        std::filesystem::copy(dir_entry.path(), path_name);
      }
    }
  }
}

void recursive_resolve_copy(std::filesystem::path input_dir_path,
                            std::filesystem::path output_dir_path,
                            std::map<std::string, std::string> resolve_map)
{
  std::printf(feta::colorize("resolving files to %s\n", feta::Color::BLUE).c_str(), output_dir_path.c_str());
  
  if (!std::filesystem::exists(output_dir_path)) {
    std::filesystem::create_directories(output_dir_path);
  }
  if (!std::filesystem::is_empty(output_dir_path)) {
    std::printf(feta::colorize("target directory (%s) is not empty.\n", feta::Color::RED).c_str(), output_dir_path.c_str());
    throw std::invalid_argument("target dir is not empty.");
  }
  // search for substrings and replace with actual
  if (std::filesystem::is_directory(input_dir_path)) {
    for (const auto& dir_entry :
         std::filesystem::recursive_directory_iterator(input_dir_path))
    {

      // the output path ("write path")
      std::string new_path = dir_entry.path().c_str();

      new_path.replace(new_path.find(input_dir_path.c_str()),
                       std::string(input_dir_path.c_str()).length(),
                       output_dir_path.c_str());

      // entry resolver
      new_path = resolve_string(new_path, resolve_map);

      std::printf(feta::colorize("resolving %s --> %s\n", feta::Color::BLUE).c_str(), dir_entry.path().filename().c_str(), new_path.c_str());

      // if file
      if (dir_entry.is_regular_file()) {
        std::ostringstream text;
        std::ifstream in_file(dir_entry.path());
        text << in_file.rdbuf();
        std::string str = text.str();

        // in-file name search
        str = resolve_string(str, resolve_map);

        in_file.close();

        std::filesystem::create_directories(
            std::filesystem::path(new_path).parent_path());

        std::ofstream out_file(new_path);
        out_file << str;
      } else if (!dir_entry.is_directory()) {
        std::filesystem::copy(dir_entry.path(), new_path);
      }
    }
  }
}

std::vector<std::filesystem::path> get_dirs_in_dir(std::filesystem::path dir)
{
  std::vector<std::filesystem::path> dirs;
  for (const auto& entry : std::filesystem::directory_iterator(dir)) {
    if (std::filesystem::is_directory(entry.path())) {
      dirs.push_back(entry.path());
    }
  }
  return dirs;
}
