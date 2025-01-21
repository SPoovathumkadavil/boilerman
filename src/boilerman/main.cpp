
#include "main.hpp"

#include <fetalib/cli/colors.hpp>
#include <fetalib/cli/arguments.hpp>

#include "boiler.hpp"

int main(int argc, char** argv)
{

  feta::ArgumentParser argparser(argc, argv);
  
  feta::ArgumentDependency c_help = feta::get_blank_argument_dependency()
    .withKey("help")
    .withHelpMessage(
      "Display the help message."
    );
  feta::ArgumentDependency c_init = feta::get_blank_argument_dependency()
    .withKey("init")
    .withHelpMessage(
      "Initialize a boilerplate."
    );
  feta::ArgumentDependency c_list = feta::get_blank_argument_dependency()
    .withKey("list")
    .withHelpMessage("List available boilerplates.");
  feta::Argument a_index = feta::get_blank_argument()
    .withKey("-i")
    .withAlternateKey("--index")
    .withOptional()
    .withWordCount(1)
    .withHelpMessage("Index of the boilerplate you are trying to initialize.");
  feta::Argument a_project_name = feta::get_blank_argument()
    .withKey("-n")
    .withAlternateKey("--name")
    .withOptional()
    .withWordCount(1)
    .withHelpMessage("Your project's name.");
  feta::Argument a_dir = feta::get_blank_argument()
    .withKey("-d")
    .withAlternateKey("--directory")
    .withOptional()
    .withWordCount(1)
    .withHelpMessage("Your project's directory.");
  argparser.add(&c_help);
  argparser.add(&c_init);
  argparser.add(&a_index, &c_init);
  argparser.add(&a_project_name, &c_init);
  argparser.add(&a_dir, &c_init);
  argparser.add(&c_list);

  // -- validation --

  feta::Validation argument_validation = argparser.validate();
  if (!argument_validation.valid) {
    std::printf("Argument Error: %s\n", argument_validation.detail.c_str());
    exit(1);
  }

  // -- init --

  auto lib = library {};
  auto boilers = lib.populate_boilers();

  // -- command parsing --

  feta::ArgumentDependency *command = argparser.get_command();

  if (command == &c_list) {
    for (int b = 0; b < (int)boilers.size(); b++) {
      std::printf(feta::colorize("%i - %s: %s (%s)\n", feta::Color::BLUE).c_str(), b + 1,
                  boilers[b]._lang.c_str(),
                  boilers[b]._desc.c_str(),
                  boilers[b]._type.c_str());
    }
  }

  if (command == &c_help) {
    std::vector<std::string> hs = argparser.get_help_message(lib._name);
    for (std::string s : hs) std::printf("%s\n", s.c_str());
  }

  if (command == &c_init) {
    int index = -1;
    std::string project_name = "";
    std::string dir = "";
    int q = 0;
    if (argparser.get<std::string>(a_index).has_value()) {
      index = argparser.get<int>(a_index).value()-1;
    }
    if (argparser.get<std::string>(a_project_name).has_value()) {
      project_name = argparser.get<std::string>(a_project_name).value();
    }
    if (argparser.get<std::string>(a_dir).has_value()) {
      dir = argparser.get<std::string>(a_dir).value();
    }

    if (index < 0 || index > boilers.size()) {
      std::printf(feta::colorize("available boilerplates:\n", feta::Color::BLUE).c_str());
      for (int b = 0; b < boilers.size(); b++) {
        std::printf(feta::colorize("%i - %s: %s (%s)\n", feta::Color::BLUE).c_str(),
                    b + 1,
                    boilers[b]._lang.c_str(),
                    boilers[b]._desc.c_str(),
                    boilers[b]._type.c_str());
      }

      int u_ind = -1;
      while (u_ind < 0) {
        std::printf(feta::colorize("enter index %i-%i: ", feta::Color::BLUE).c_str(), 1, (int)boilers.size());
        std::cin >> u_ind;
        if (u_ind < 1 || u_ind > boilers.size())
          u_ind = -1;
      }
      index = u_ind - 1;
    }

    if (project_name == "") {
      // read project name
      std::printf(feta::colorize("project name: ", feta::Color::BLUE).c_str());
      std::cin >> project_name;
    }

    if (dir == "") {
      // read boiler destination directory
      std::printf(feta::colorize("destination directory: ", feta::Color::BLUE).c_str());
      std::cin >> dir;
    }

    // construct resolve map
    std::map<std::string, std::string> resolve_map;
    resolve_map["name"] = project_name;
    boilers[index].use(dir, resolve_map);
  }

  return 0;
}
