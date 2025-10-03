#pragma once

#include <filesystem>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>

// -- file utils --

const static std::filesystem::path bp_dir =
    std::filesystem::path(getenv("HOME"))
        .append(".local/library/boilerman/boilerplates");

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

std::vector<boilerplate> load_boilerplates();
std::string get_printable(boilerplate *b);
int main(int argc, char **argv);
