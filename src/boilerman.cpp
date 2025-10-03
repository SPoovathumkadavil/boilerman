
#include "boilerman.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>

std::vector<std::filesystem::path>
get_all_directories(std::filesystem::path dir) {
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
    throw std::invalid_argument("path does not lead to a regular file.");
  std::ostringstream text;
  std::ifstream f(path);
  text << f.rdbuf();
  f.close();
  return text.str();
}

std::vector<std::string> find_var_names(std::filesystem::path dir,
                                        std::string var_key) {
  std::vector<std::string> vars;
  for (std::filesystem::recursive_directory_iterator e(dir);
       e != std::filesystem::recursive_directory_iterator(); ++e) {
    const auto &entry = *e;
    if (entry.path().filename().string().substr(0, 1) == "~") {
      e.disable_recursion_pending();
    }
    std::string s = entry.path().parent_path().string();
    if (std::filesystem::is_regular_file(entry))
      s += read_file(entry);
    std::string v_name = "";
    bool capturing = false;
    for (int i = 0; i < s.length() - var_key.length(); i++) {
      if (s.substr(i, var_key.length()) == var_key) {
        if (capturing) {
          if (std::find(vars.begin(), vars.end(), v_name) == vars.end())
            vars.push_back(v_name);
          v_name = "";
        }
        capturing = !capturing;
        i += var_key.length();
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
  std::string ret = "";
  std::string v_name = "";
  bool capturing = false;
  for (int i = 0; i < s.length(); i++) {
    if (i <= s.length() - var_key.length()) {
      if (s.substr(i, var_key.length()) == var_key) {
        if (capturing) {
          ret += resolve_map[v_name];
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
  if (capturing && !v_name.empty()) {
    ret += resolve_map[v_name];
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
      std::filesystem::copy(entry.path(), new_path);
    } else if (entry.is_directory()) {
      std::filesystem::create_directory(new_path);
    } else {
      std::filesystem::copy(entry.path(), new_path);
    }
  }
}

void resolve_copy(std::filesystem::path from, std::filesystem::path to,
                  std::string var_key,
                  std::map<std::string, std::string> resolve_map) {
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
      out_stream.close();

    } else if (entry.is_directory() && !direct_copy) {
      std::filesystem::create_directory(new_path);
    } else {
      recursive_copy(entry.path(), new_path);
    }
  }
}

std::vector<boilerplate> load_boilerplates() {
  std::vector<boilerplate> bps;
  for (const std::filesystem::path &d : get_all_directories(bp_dir)) {
    // get tag info from folder name.
    // eg. "tag1:a;tagb:a;"
    std::string name;
    std::map<std::string, std::string> tags;
    std::string fn = d.filename();
    std::string cap_t = "";
    std::string cap_v = "";
    int cc = 0;
    for (int i = 0; i < fn.length(); i++) {
      if (fn.substr(i, 1) == "-")
        cc = 1;
      else if (fn.substr(i, 1) == ";") {
        cc = 1;
        tags[cap_t] = cap_v;
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
    bps.push_back(boilerplate{d, name, tags});
  }
  return bps;
}

std::string get_printable(boilerplate *b) {
  std::string str = b->name;
  for (std::map<std::string, std::string>::iterator it = b->tags.begin();
       it != b->tags.end(); ++it) {
    str += "\n";
    str += it->first;
    str += ": ";
    str += it->second;
  }
  return str;
}

int main(int argc, char **argv) {
  std::vector<boilerplate> bps = load_boilerplates();
  std::printf("Available boilerplates:\n");
  for (int i = 0; i < bps.size(); i++) {
    std::printf("%i) %s\n-----\n", i, get_printable(&bps.at(i)).c_str());
  }
  std::printf("Choice (index): ");
  int chosen_index;
  std::cin >> chosen_index;

  boilerplate bp = bps.at(chosen_index);
  std::vector<std::string> vars = find_var_names(bp.src_dir, "|||");
  std::map<std::string, std::string> res_map;
  for (std::string var : vars) {
    std::printf("Project Detail -- %s: ", var.c_str());
    std::string val;
    std::cin >> val;
    res_map[var] = val;
  }

  std::printf("Directory: ");
  std::string dir;
  std::cin >> dir;

  resolve_copy(bp.src_dir, dir, "|||", res_map);

  std::printf("Project Created.\n");
}
