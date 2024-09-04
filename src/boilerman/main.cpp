
#include "main.hpp"

#include <fmt/color.h>

#include "boiler.hpp"

int main(int argc, char** argv)
{
  auto lib = library {};
  auto boilers = lib.populate_boilers();

  if (argc < 2) {
    fmt::print(fg(fmt::color::pale_violet_red),
               "error: no arguments provided.\ntry {} --help for usage "
               "instructions.\n",
               lib._name);
    return 1;
  }

  std::string project_name = "project";
  std::filesystem::path dir = ".";
  int b_index = -1;

  for (int i = 0; i < argc; i++) {
    if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
      fmt::print(fg(fmt::color::sky_blue),
                 "usage: {} [options] [command]\n",
                 lib._name);
      fmt::print(fg(fmt::color::sky_blue), "options:\n");
      fmt::print(fg(fmt::color::sky_blue),
                 "\t-n, --name [name]\t\tset name.\n");
      fmt::print(fg(fmt::color::sky_blue), "commands:\n");
      fmt::print(fg(fmt::color::sky_blue),
                 "\ti, init [index]\t\tinitialize a boilerplate.\n");
      fmt::print(fg(fmt::color::sky_blue),
                 "\ta, add [dir]\t\tadd a boilerplate.\n");
      fmt::print(fg(fmt::color::sky_blue),
                 "\t-h, --help\t\tshow this help message.\n");
      fmt::print(fg(fmt::color::sky_blue),
                 "\t-l, --list\t\tlist available boilerplates.\n");
      return 0;
    }

    if (std::string(argv[i]) == "--list" || std::string(argv[i]) == "-l") {
      for (int b = 0; b < (int)boilers.size(); b++) {
        fmt::print(fg(fmt::color::sky_blue),
                   "{} - {}: {} ({})\n",
                   b + 1,
                   boilers[b]._lang,
                   boilers[b]._desc,
                   boilers[b]._type);
      }
      return 0;
    }

    if (std::string(argv[i]) == "init" || std::string(argv[i]) == "i") {
      if (i + 1 >= argc) {
        fmt::print(fg(fmt::color::sky_blue), "available boilerplates:\n");
        for (int b = 0; b < (int)boilers.size(); b++) {
          fmt::print(fg(fmt::color::sky_blue),
                     "\t {}. {} := {} ({})\n",
                     b + 1,
                     boilers[b]._lang,
                     boilers[b]._desc,
                     boilers[b]._type);
        }

        // read boiler index
        int u_ind = -1;
        while (u_ind < 0) {
          fmt::print(fg(fmt::color::sky_blue), "enter index {}-{}: ", 1, (int)boilers.size());
          std::cin >> u_ind;
          if (u_ind < 1 || u_ind > (int)boilers.size()) u_ind = -1;
        }
        b_index = u_ind-1;

        // read project name
        fmt::print(fg(fmt::color::sky_blue), "project name: ");
        std::cin >> project_name;
        
        // read boiler destination directory
        fmt::print(fg(fmt::color::sky_blue), "destination directory: ");
        std::cin >> dir;
      } else {
        b_index = std::stoi(argv[i + 1])-1;

        if (i + 2 < argc)
          dir = std::string(argv[i + 2]);
      }
    }

    if (std::string(argv[i]) == "--name" || std::string(argv[i]) == "-n") {
      if (i + 1 >= argc) {
        fmt::print(fg(fmt::color::pale_violet_red),
                   "error: project name not provided.\ntry {} --help for usage "
                   "instructions.\n",
                   lib._name);
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
