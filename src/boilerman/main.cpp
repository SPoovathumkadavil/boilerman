
#include "main.hpp"

#include <fetalib/cli/colors.hpp>

#include "boiler.hpp"

int main(int argc, char** argv)
{
  auto lib = library {};
  auto boilers = lib.populate_boilers();

  if (argc < 2) {
    std::printf(feta::colorize("error: no arguments provided.\ntry %s --help for usage instructions.\n", feta::Color::RED).c_str(), lib._name.c_str());
    return 1;
  }

  std::string project_name = "project";
  std::filesystem::path dir = ".";
  int b_index = -1;

  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
      std::printf(feta::colorize("usage: %s [options] [command]\n", feta::Color::BLUE).c_str(), lib._name.c_str());
      std::printf(feta::colorize("options:\n", feta::Color::BLUE).c_str());
      std::printf(feta::colorize("\t-n, --name [name]\t\tset name.\n", feta::Color::BLUE).c_str());
      std::printf(feta::colorize("commands:\n", feta::Color::BLUE).c_str());
      std::printf(feta::colorize("\ti, init [index]\t\tinitialize a boilerplate.\n", feta::Color::BLUE).c_str());
      std::printf(feta::colorize("\ta, add [dir]\t\tadd a boilerplate.\n", feta::Color::BLUE).c_str());
      std::printf(feta::colorize("\t-h, --help\t\tshow this help message.\n", feta::Color::BLUE).c_str());
      std::printf(feta::colorize("\t-l, --list\t\tlist available boilerplates.\n", feta::Color::BLUE).c_str());
      return 0;
    }

    if (std::string(argv[i]) == "--list" || std::string(argv[i]) == "-l") {
      for (int b = 0; b < (int)boilers.size(); b++) {
        std::printf(feta::colorize("%i - %s: %s (%s)\n", feta::Color::BLUE).c_str(), b + 1,
                   boilers[b]._lang.c_str(),
                   boilers[b]._desc.c_str(),
                   boilers[b]._type.c_str());
      }
      return 0;
    }

    if (std::string(argv[i]) == "init" || std::string(argv[i]) == "i") {
      if (i + 1 >= argc) {
        std::printf(feta::colorize("available boilerplates:\n", feta::Color::BLUE).c_str());
        for (int b = 0; b < (int)boilers.size(); b++) {
          std::printf(feta::colorize("%i - %s: %s (%s)\n", feta::Color::BLUE).c_str(), b + 1,
                      boilers[b]._lang.c_str(),
                      boilers[b]._desc.c_str(),
                      boilers[b]._type.c_str());
        }

        // read boiler index
        int u_ind = -1;
        while (u_ind < 0) {
          std::printf(feta::colorize("enter index %i-%i: ", feta::Color::BLUE).c_str(), 1, (int)boilers.size());
          std::cin >> u_ind;
          if (u_ind < 1 || u_ind > (int)boilers.size())
            u_ind = -1;
        }
        b_index = u_ind - 1;

        // read project name
        std::printf(feta::colorize("project name: ", feta::Color::BLUE).c_str());
        std::cin >> project_name;
        // read boiler destination directory
        std::printf(feta::colorize("destination directory: ", feta::Color::BLUE).c_str());
        std::cin >> dir;
      } else {
        b_index = std::stoi(argv[i + 1]) - 1;

        if (i + 2 < argc)
          dir = std::string(argv[i + 2]);
      }
    }

    if (std::string(argv[i]) == "--name" || std::string(argv[i]) == "-n") {
      if (i + 1 >= argc) {
        std::printf(feta::colorize("error: project name not provided.\ntry %s --help for usage instructions.\n", feta::Color::RED).c_str(), lib._name.c_str());
        return 1;
      }

      project_name = std::string(argv[i + 1]);
    }
  }

  // construct resolve map
  std::map<std::string, std::string> resolve_map;
  resolve_map["name"] = project_name;

  if (b_index >= 0) {
    boilers[b_index].use(dir, resolve_map);
  }

  return 0;
}
