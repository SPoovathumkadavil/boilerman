#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

// -- file utils --

std::vector<std::filesystem::path> get_all_directories(std::filesystem::path p);
std::string read_file(std::filesystem::path path);
std::vector<std::string> find_var_names(std::filesystem::path dir,
                                        std::string var_key);
std::string resolve_string(std::string s, std::string var_key,
                           std::map<std::string, std::string> resolve_map);
void resolve_copy(std::filesystem::path from, std::filesystem::path to,
                  std::string var_key,
                  std::map<std::string, std::string> resolve_map);

// -- app functions --

struct boilerplate {
  std::filesystem::path src_dir;
  std::string name;
  std::map<std::string, std::string> tags;
};

std::filesystem::path default_boilerplate_dir();
boilerplate parse_boilerplate_dir(std::filesystem::path dir);
std::vector<boilerplate>
load_boilerplates(std::filesystem::path boilerplate_dir =
                      default_boilerplate_dir());
std::string get_printable(const boilerplate &b);
int run_interactive_app();
