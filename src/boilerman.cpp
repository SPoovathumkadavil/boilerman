
#include "boilerman.hpp"

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::vector<std::filesystem::path>
get_all_directories(std::filesystem::path dir) {
  if (!std::filesystem::exists(dir)) {
    throw std::invalid_argument("directory does not exist: " + dir.string());
  }
  if (!std::filesystem::is_directory(dir)) {
    throw std::invalid_argument("path is not a directory: " + dir.string());
  }

  std::vector<std::filesystem::path> dirs;
  for (const auto &entry : std::filesystem::directory_iterator(dir)) {
    if (std::filesystem::is_directory(entry)) {
      dirs.push_back(entry);
    }
  }
  return dirs;
}

std::string read_file(std::filesystem::path path) {
  if (!std::filesystem::is_regular_file(path))
    throw std::invalid_argument("path does not lead to a regular file: " +
                                path.string());
  std::ostringstream text;
  std::ifstream f(path);
  if (!f) {
    throw std::runtime_error("failed to open file: " + path.string());
  }
  text << f.rdbuf();
  return text.str();
}

std::vector<std::string> find_var_names(std::filesystem::path dir,
                                        std::string var_key) {
  if (var_key.empty()) {
    throw std::invalid_argument("var_key cannot be empty.");
  }

  std::vector<std::string> vars;
  for (std::filesystem::recursive_directory_iterator e(dir);
       e != std::filesystem::recursive_directory_iterator(); ++e) {
    const auto &entry = *e;
    if (entry.path().filename().string().substr(0, 1) == "~") {
      e.disable_recursion_pending();
      continue;
    }
    std::string s = entry.path().string();
    if (std::filesystem::is_regular_file(entry))
      s += read_file(entry);
    std::string v_name = "";
    bool capturing = false;
    for (std::size_t i = 0; i < s.length(); i++) {
      if (s.substr(i, var_key.length()) == var_key) {
        if (capturing) {
          if (std::find(vars.begin(), vars.end(), v_name) == vars.end())
            vars.push_back(v_name);
          v_name = "";
        }
        capturing = !capturing;
        i += var_key.length() - 1;
        continue;
      }
      if (capturing) {
        v_name += s.substr(i, 1);
      }
    }
  }
  return vars;
}

std::string resolve_string(std::string s, std::string var_key,
                           std::map<std::string, std::string> resolve_map) {
  if (var_key.empty()) {
    throw std::invalid_argument("var_key cannot be empty.");
  }

  std::string ret = "";
  std::string v_name = "";
  bool capturing = false;
  for (std::size_t i = 0; i < s.length(); i++) {
    if (i + var_key.length() <= s.length()) {
      if (s.substr(i, var_key.length()) == var_key) {
        if (capturing) {
          const auto resolved = resolve_map.find(v_name);
          if (resolved == resolve_map.end()) {
            throw std::invalid_argument("missing value for variable: " +
                                        v_name);
          }
          ret += resolved->second;
          v_name = "";
        }
        capturing = !capturing;
        i += var_key.length() - 1;
        continue;
      }
    }
    if (capturing)
      v_name += s.at(i);
    else
      ret += s.at(i);
  }
  if (capturing) {
    throw std::invalid_argument("unclosed variable: " + v_name);
  }
  return ret;
}

void recursive_copy(std::filesystem::path from, std::filesystem::path to) {
  std::filesystem::create_directories(to);
  for (std::filesystem::recursive_directory_iterator e(from);
       e != std::filesystem::recursive_directory_iterator(); ++e) {
    const auto &entry = *e;
    std::string new_path =
        entry.path().string().replace(entry.path().string().find(from.string()),
                                      from.string().length(), to.string());
    if (entry.is_regular_file()) {
      std::filesystem::create_directories(
          std::filesystem::path(new_path).parent_path());
      std::filesystem::copy(entry.path(), new_path,
                            std::filesystem::copy_options::overwrite_existing);
    } else if (entry.is_directory()) {
      std::filesystem::create_directories(new_path);
    } else {
      std::filesystem::copy(entry.path(), new_path,
                            std::filesystem::copy_options::overwrite_existing);
    }
  }
}

void copy_direct(std::filesystem::path from, std::filesystem::path to) {
  if (std::filesystem::is_directory(from)) {
    recursive_copy(from, to);
    return;
  }

  std::filesystem::create_directories(to.parent_path());
  std::filesystem::copy(from, to,
                        std::filesystem::copy_options::overwrite_existing);
}

void resolve_copy(std::filesystem::path from, std::filesystem::path to,
                  std::string var_key,
                  std::map<std::string, std::string> resolve_map) {
  if (!std::filesystem::exists(from)) {
    throw std::invalid_argument("source directory does not exist: " +
                                from.string());
  }
  if (!std::filesystem::is_directory(from)) {
    throw std::invalid_argument("source path is not a directory: " +
                                from.string());
  }
  if (std::filesystem::exists(to)) {
    throw std::invalid_argument("destination already exists: " + to.string());
  }

  std::filesystem::create_directories(to);
  for (std::filesystem::recursive_directory_iterator e(from);
       e != std::filesystem::recursive_directory_iterator(); ++e) {
    const auto &entry = *e;
    std::string new_path =
        entry.path().string().replace(entry.path().string().find(from.string()),
                                      from.string().length(), to.string());
    new_path = resolve_string(new_path, var_key, resolve_map);
    bool direct_copy = false;
    if (entry.path().filename().string().substr(0, 1) == "~") {
      e.disable_recursion_pending();
      new_path = std::filesystem::path(new_path).parent_path() /
                 entry.path().filename().string().substr(1);
      direct_copy = true;
    }
    if (entry.is_regular_file() && !direct_copy) {
      std::filesystem::create_directories(
          std::filesystem::path(new_path).parent_path());
      std::ofstream out_stream(new_path);
      out_stream << resolve_string(read_file(entry.path()), var_key,
                                   resolve_map);
      if (!out_stream) {
        throw std::runtime_error("failed to write file: " + new_path);
      }

    } else if (entry.is_directory() && !direct_copy) {
      std::filesystem::create_directories(new_path);
    } else {
      copy_direct(entry.path(), new_path);
    }
  }
}

std::filesystem::path default_boilerplate_dir() {
  const char *configured_dir = std::getenv("BOILERMAN_LIBRARY_DIR");
  if (configured_dir != nullptr && configured_dir[0] != '\0') {
    return std::filesystem::path(configured_dir) / "boilerplates";
  }

  const char *home = std::getenv("HOME");
  if (home == nullptr || home[0] == '\0') {
    throw std::runtime_error(
        "HOME is not set; set BOILERMAN_LIBRARY_DIR or HOME.");
  }

  return std::filesystem::path(home) / ".local/library/boilerman/boilerplates";
}

boilerplate parse_boilerplate_dir(std::filesystem::path dir) {
  std::string name;
  std::map<std::string, std::string> tags;
  std::string fn = dir.filename();
  std::string cap_t = "";
  std::string cap_v = "";
  int cc = 0;
  for (std::size_t i = 0; i < fn.length(); i++) {
    if (fn.substr(i, 1) == "-")
      cc = 1;
    else if (fn.substr(i, 1) == ";") {
      cc = 1;
      if (!cap_t.empty()) {
        tags[cap_t] = cap_v;
      }
      cap_t = "";
      cap_v = "";
    } else if (fn.substr(i, 1) == ":")
      cc = 2;
    else if (cc == 1)
      cap_t += fn.substr(i, 1);
    else if (cc == 2)
      cap_v += fn.substr(i, 1);
    else
      name += fn.substr(i, 1);
  }
  return boilerplate{dir, name, tags};
}

std::vector<boilerplate>
load_boilerplates(std::filesystem::path boilerplate_dir) {
  std::vector<boilerplate> bps;
  for (const std::filesystem::path &d : get_all_directories(boilerplate_dir)) {
    bps.push_back(parse_boilerplate_dir(d));
  }
  return bps;
}

std::string get_printable(const boilerplate &b) {
  std::string str = b.name;
  for (std::map<std::string, std::string>::const_iterator it = b.tags.begin();
       it != b.tags.end(); ++it) {
    str += "\n";
    str += it->first;
    str += ": ";
    str += it->second;
  }
  return str;
}

int run_interactive_app() {
  std::vector<boilerplate> bps = load_boilerplates();
  if (bps.empty()) {
    std::cerr << "No boilerplates found in " << default_boilerplate_dir()
              << ".\n";
    return 1;
  }

  std::printf("Available boilerplates:\n");
  for (std::size_t i = 0; i < bps.size(); i++) {
    std::printf("%zu) %s\n-----\n", i, get_printable(bps.at(i)).c_str());
  }
  std::printf("Choice (index): ");
  std::size_t chosen_index;
  if (!(std::cin >> chosen_index) || chosen_index >= bps.size()) {
    std::cerr << "Invalid boilerplate index.\n";
    return 1;
  }

  boilerplate bp = bps.at(chosen_index);
  std::vector<std::string> vars = find_var_names(bp.src_dir, "|||");
  std::map<std::string, std::string> res_map;
  std::cin.ignore();
  for (std::string var : vars) {
    std::printf("Project Detail -- %s: ", var.c_str());
    std::string val;
    std::getline(std::cin, val);
    res_map[var] = val;
  }

  std::printf("Directory: ");
  std::string dir;
  if (!(std::cin >> dir) || dir.empty()) {
    std::cerr << "Invalid destination directory.\n";
    return 1;
  }

  resolve_copy(bp.src_dir, dir, "|||", res_map);

  std::printf("Project Created.\n");
  return 0;
}
