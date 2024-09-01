
#include <fstream>
#include <sstream>
#include <vector>
#include <fmt/color.h>
#include "fileutil.hpp"

void recursive_resolve_copy(std::filesystem::path input_dir_path,
                            std::filesystem::path output_dir_path,
                            std::string name)
{
  fmt::print(fg(fmt::color::sky_blue),
             "resolving files to {}\n",
             std::string(output_dir_path));
  if (!std::filesystem::exists(output_dir_path)) {
    std::filesystem::create_directories(output_dir_path);
  }
  if (!std::filesystem::is_empty(output_dir_path)) {
    fmt::print(fg(fmt::color::pale_violet_red),
               "target directory is not empty.\n");
    throw std::invalid_argument("target dir is not empty.");
  }
  // search for substrings and replace with actual
  if (std::filesystem::is_directory(input_dir_path)) {
    for (const auto& dirEntry :
         std::filesystem::recursive_directory_iterator(input_dir_path))
    {
      // the output path ("write path")
      std::string new_path = dirEntry.path().c_str();
      new_path.replace(new_path.find(input_dir_path.c_str()),
                       std::string(input_dir_path.c_str()).length(),
                       output_dir_path.c_str());

      // entry resolver
      std::string name_search = "[[name]]";
      std::string capital_name_search = "[%C[name]%C]";
      while (new_path.find(name_search) != std::string::npos) {
        new_path.replace(
            new_path.find(name_search), name_search.length(), name);
      }
      std::string capname = name;
      std::transform(
          capname.begin(), capname.end(), capname.begin(), ::toupper);
      while (new_path.find(capital_name_search) != std::string::npos) {
        new_path.replace(new_path.find(capital_name_search),
                         capital_name_search.length(),
                         capname);
      }

      fmt::print(fg(fmt::color::sky_blue),
                 "resolving {} --> {}\n",
                 std::string(dirEntry.path().filename()),
                 std::string(new_path));

      // if file
      if (dirEntry.is_regular_file()) {
        std::ostringstream text;
        std::ifstream in_file(dirEntry.path());
        text << in_file.rdbuf();
        std::string str = text.str();

        // in-file name search
        while (str.find(name_search) != std::string::npos) {
          str.replace(str.find(name_search), name_search.length(), name);
        }
        while (str.find(capital_name_search) != std::string::npos) {
          str.replace(str.find(capital_name_search),
                      capital_name_search.length(),
                      capname);
        }

        in_file.close();

        std::filesystem::create_directories(
            std::filesystem::path(new_path).parent_path());

        std::ofstream out_file(new_path);
        out_file << str;
      } else if (!dirEntry.is_directory()) {
        std::filesystem::copy(dirEntry.path(), new_path);
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
};