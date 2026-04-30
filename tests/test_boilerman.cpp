#include "boilerman.hpp"

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

void require(bool condition, const std::string &message) {
  if (!condition) {
    throw std::runtime_error(message);
  }
}

std::filesystem::path make_temp_dir() {
  const auto stamp =
      std::chrono::steady_clock::now().time_since_epoch().count();
  std::filesystem::path dir =
      std::filesystem::temp_directory_path() /
      ("boilerman_test_" + std::to_string(stamp));
  std::filesystem::create_directories(dir);
  return dir;
}

void write_file(const std::filesystem::path &path, const std::string &text) {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream out(path);
  out << text;
}

bool contains(const std::vector<std::string> &values,
              const std::string &needle) {
  return std::find(values.begin(), values.end(), needle) != values.end();
}

void test_resolve_string() {
  const std::map<std::string, std::string> values{{"name", "demo"},
                                                  {"kind", "app"}};
  require(resolve_string("|||name|||/|||kind|||", "|||", values) ==
              "demo/app",
          "resolve_string replaces all variables");

  bool threw = false;
  try {
    resolve_string("|||missing|||", "|||", values);
  } catch (const std::invalid_argument &) {
    threw = true;
  }
  require(threw, "resolve_string rejects missing variables");
}

void test_parse_boilerplate_dir() {
  const boilerplate bp = parse_boilerplate_dir(
      "/tmp/cpp_app-language:cpp;build_system:Makefile;");
  require(bp.name == "cpp_app", "parse_boilerplate_dir extracts name");
  require(bp.tags.at("language") == "cpp",
          "parse_boilerplate_dir extracts language tag");
  require(bp.tags.at("build_system") == "Makefile",
          "parse_boilerplate_dir extracts build system tag");
}

void test_find_var_names() {
  const std::filesystem::path root = make_temp_dir();
  write_file(root / "src" / "|||name|||.cpp",
             "project |||name||| uses |||language|||");
  write_file(root / "~literal" / "ignored.txt", "|||ignored|||");
  write_file(root / "~raw.txt", "|||also_ignored|||");

  const std::vector<std::string> vars = find_var_names(root, "|||");
  require(contains(vars, "name"), "find_var_names finds filename variables");
  require(contains(vars, "language"), "find_var_names finds file variables");
  require(!contains(vars, "ignored"),
          "find_var_names skips direct-copy directories");
  require(!contains(vars, "also_ignored"),
          "find_var_names skips direct-copy files");

  std::filesystem::remove_all(root);
}

void test_resolve_copy() {
  const std::filesystem::path root = make_temp_dir();
  const std::filesystem::path src = root / "template";
  const std::filesystem::path dst = root / "out";
  write_file(src / "include" / "|||name|||.hpp", "#pragma once\n");
  write_file(src / "src" / "main.cpp", "int main() { return |||code|||; }\n");
  write_file(src / "~raw.txt", "keep |||literal|||");

  resolve_copy(src, dst, "|||", {{"name", "demo"}, {"code", "0"}});

  require(std::filesystem::is_regular_file(dst / "include" / "demo.hpp"),
          "resolve_copy resolves destination paths");
  require(read_file(dst / "src" / "main.cpp") == "int main() { return 0; }\n",
          "resolve_copy resolves file contents");
  require(read_file(dst / "raw.txt") == "keep |||literal|||",
          "resolve_copy direct-copies tilde-prefixed files");

  bool threw = false;
  try {
    resolve_copy(src, dst, "|||", {{"name", "demo"}, {"code", "0"}});
  } catch (const std::invalid_argument &) {
    threw = true;
  }
  require(threw, "resolve_copy rejects existing destinations");

  std::filesystem::remove_all(root);
}

} // namespace

int main() {
  try {
    test_resolve_string();
    test_parse_boilerplate_dir();
    test_find_var_names();
    test_resolve_copy();
  } catch (const std::exception &e) {
    std::cerr << "test failed: " << e.what() << "\n";
    return 1;
  }

  std::cout << "All tests passed.\n";
  return 0;
}
