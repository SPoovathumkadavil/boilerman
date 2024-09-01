
#include "main.hpp"

#include <fmt/color.h>

#include "boiler.hpp"

int main(int argc, char** argv)
{
  auto lib = library {};
  auto boilers = lib.populate_boilers();

  if (argc < 2) {
    fmt::print(
        fg(fmt::color::red),
        "error: no arguments provided.\ntry {} --help for usage instructions.",
        lib._name);
    return 1;
  }

  std::string project_name = "project";
  std::filesystem::path dir = ".";
  int b_index = -1;

  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
      fmt::print(
          fg(fmt::color::cyan), "usage: {} [options] [command]\n", lib._name);
      fmt::print(fg(fmt::color::cyan), "options:\n");
      fmt::print(fg(fmt::color::cyan), "\t-n, --name [name]\t\tset name.\n");
      fmt::print(fg(fmt::color::cyan), "commands:\n");
      fmt::print(fg(fmt::color::cyan),
                 "\ti, init [index]\t\tinitialize a boilerplate.\n");
      fmt::print(fg(fmt::color::cyan),
                 "\t-h, --help\t\tshow this help message.\n");
      fmt::print(fg(fmt::color::cyan),
                 "\t-l, --list\t\tlist available boilerplates.\n");
      return 0;
    }

    if (std::string(argv[i]) == "--list" || std::string(argv[i]) == "-l") {
      for (int b = 0; b < (int)boilers.size(); b++) {
        fmt::print(fg(fmt::color::cyan),
                   "{}. {}: {} ({})\n",
                   b + 1,
                   boilers[b]._lang,
                   boilers[b]._desc,
                   boilers[b]._type);
      }
      return 0;
    }

    if (std::string(argv[i]) == "init" || std::string(argv[i]) == "i") {
      if (i + 1 < argc) {
        fmt::print(fg(fmt::color::red),
                    "error: boiler index not provided.\ntry {} --help for "
                    "usage instructions.",
                    lib._name);
        return 1;
      }

      b_index = std::stoi(argv[i + 1]);

      if (i + 2 < argc)
        dir = std::string(argv[i + 2]);
    }

    if (std::string(argv[i]) == "--name" || std::string(argv[i]) == "-n") {
      if (i + 1 < argc) {
        fmt::print(fg(fmt::color::red),
                   "error: project name not provided.\ntry {} --help for usage "
                   "instructions.",
                   lib._name);
        return 1;
      }

      project_name = std::string(argv[i + 1]);
    }
  }

  if (b_index >= 0) {
    boilers[b_index].use(dir, project_name);
  }

  return 0;
}