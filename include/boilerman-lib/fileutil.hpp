#pragma once

#include <string>
#include <filesystem>

void recursive_resolve_copy(std::filesystem::path input_dir_path, std::filesystem::path output_dir_path, std::string name);

std::vector<std::filesystem::path> get_files_in_dir(std::filesystem::path dir);