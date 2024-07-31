#include "boilermanager.h"
#include "fileutils.h"
#include <iostream>
#include <stdio.h>

void BoilerManager::loadBoilers()
{
	std::printf("Loading boilerplates from %s\n", DEPENDENCIES_DIR.c_str());
	std::vector<std::string> boilerDirs = get_dirs_in_dir(DEPENDENCIES_DIR);
	for (const std::string &dir : boilerDirs)
	{
		std::string dirname = dir.substr(dir.find_last_of("/\\") + 1);
		std::string name = dirname.substr(dirname.find_first_of("_") + 1, dirname.find_last_of(".") - dirname.find_first_of("_") - 1);
		std::string desc = dirname.substr(0, dirname.find_first_of("_"));
		std::string ext = dirname.substr(dirname.find_last_of(".") + 1);
		Boiler b = Boiler();
		b.setName(dirname);
		b.setDescription(desc);
		b.setType(ext);
		b.setLanguage(name);
		boilers.push_back(b);
	}
}

Boiler BoilerManager::findBoiler(const std::string &name)
{
	for (const Boiler &boiler : boilers)
	{
		if (boiler.name() == name)
		{
			return boiler;
		}
	}
	return Boiler();
}

std::vector<Boiler> BoilerManager::getBoilers() const
{
	return boilers;
}

void handle_test_args(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		// flags -d and -c to change dependencies and config directories
		if (std::string(argv[i]) == "-d")
		{
			if (i + 1 < argc)
			{
				DEPENDENCIES_DIR = argv[i + 1];
			}
		}
		if (std::string(argv[i]) == "-c")
		{
			if (i + 1 < argc)
			{
				CONFIG_DIR = argv[i + 1];
			}
		}
		// alternatively use -t to set test mode and change dirs automatically
		if (std::string(argv[i]) == "-t")
		{
			DEPENDENCIES_DIR = "dependencies";
			CONFIG_DIR = "config";
		}
	}
}

int main(int argc, char **argv)
{

	handle_test_args(argc, argv);

	// init the boiler manager
	BoilerManager manager;
	manager.loadBoilers();

	if (argc < 2)
	{
		std::cerr << "error: No arguments provided" << std::endl;
		std::cerr << "try '" + PROJECT_NAME + " --help' for more information." << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h")
		{
			std::cout << "usage: " + PROJECT_NAME + " [options] [boilerplate name]" << std::endl;
			std::cout << "options:" << std::endl;
			std::cout << "  -h, --help\t\tshow this help message" << std::endl;
			std::cout << "  -l, --list\t\tlist all available boilerplates" << std::endl;
			std::cout << "  -i, --init [name]\tinitialize a boilerplate" << std::endl;
			std::cout << "  -d [dir]\t\tset the dependencies directory" << std::endl;
			std::cout << "  -c [dir]\t\tset the config directory" << std::endl;
			std::cout << "  -t\t\t\tset test mode" << std::endl;
			return 0;
		}
		if (std::string(argv[i]) == "--list" || std::string(argv[i]) == "-l")
		{
			for (int b = 0; b < (int)manager.getBoilers().size(); b++)
			{
				// pretty print boilerplate info with index
				std::printf("%d. %s: %s (%s)\n", b + 1, manager.getBoilers()[b].language().c_str(), manager.getBoilers()[b].description().c_str(), manager.getBoilers()[b].type().c_str());
			}
			return 0;
		}
		if (std::string(argv[i]) == "--init" || std::string(argv[i]) == "-i")
		{
			if (i + 1 < argc)
			{
				// check if the argument is a number
				if (std::string(argv[i + 1]).find_first_not_of("0123456789") != std::string::npos)
				{
					// find boilerplate by name
					Boiler boiler = manager.findBoiler(argv[i + 1]);
					if (boiler.name() == "")
					{
						std::cerr << "error: invalid boilerplate name" << std::endl;
						return 1;
					}
					std::cout << "boilerplate used: " << boiler.name() << std::endl;
					// copy boilerplate to current directory
					std::string boilerDir = DEPENDENCIES_DIR + "/" + boiler.name();
					std::filesystem::copy(boilerDir, std::filesystem::current_path(), std::filesystem::copy_options::recursive);
					return 0;
				}
				else
				{
					// find boilerplate by index
					int index = std::stoi(argv[i + 1]);
					if (index < 1 || index > (int)manager.getBoilers().size())
					{
						std::cerr << "error: Invalid boilerplate index" << std::endl;
						return 1;
					}
					Boiler boiler = manager.getBoilers()[index - 1];
					std::cout << "boilerplate used: " << boiler.name() << std::endl;
					std::string boilerDir = DEPENDENCIES_DIR + "/" + boiler.name();
					std::filesystem::copy(boilerDir, std::filesystem::current_path(), std::filesystem::copy_options::recursive);
					return 0;
				}
			}
		}
	}

	return 0;
}
