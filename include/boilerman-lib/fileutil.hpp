#pragma once

#include <string>
#include <filesystem>
#include <map>

std::string resolve_string(std::string str, std::map<std::string, std::string> resolve_map);
void recursive_resolve(std::filesystem::path dir_path, std::map<std::string, std::string> resolve_map);
void recursive_resolve_copy(std::filesystem::path input_dir_path, std::filesystem::path output_dir_path, std::map<std::string, std::string> resolve_map);

std::vector<std::filesystem::path> get_dirs_in_dir(std::filesystem::path dir);