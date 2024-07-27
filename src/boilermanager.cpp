#include "boilermanager.h"
#include "fileutils.h"
#include <iostream>

void BoilerManager::loadBoilers() {
	std::vector<std::string> boilerDirs = get_dirs_in_dir(DEPENDENCIES_DIR);
	for (const std::string& dir : boilerDirs) {
		// split at . left is language right is type
		std::string dirname = dir.substr(dir.find_last_of("/\\") + 1);
		std::string name = dirname.substr(0, dirname.find_last_of("."));
		std::string ext = dirname.substr(dirname.find_last_of(".") + 1);
		Boiler b = Boiler();
		b.setName(dirname);
		if (ext == "cmake") {
			b.setType(BoilerType::CMake);
		} else if (ext == "makefile") {
			b.setType(BoilerType::Makefile);
		} else {
			b.setType(BoilerType::Unknown);
		}
		if (name == "cpp") {
			b.setLanguage(BoilerLanguage::Cpp);
		} else if (name == "c") {
			b.setLanguage(BoilerLanguage::C);
		} else {
			b.setLanguage(BoilerLanguage::Unknown);
		}
		boilers.push_back(b);
	}
}

Boiler BoilerManager::findBoiler(const std::string& name) {
	for (const Boiler& boiler : boilers) {
		if (boiler.name() == name) {
			return boiler;
		}
	}
	return Boiler();
}

std::vector<Boiler> BoilerManager::getBoilers() const {
	return boilers;
}

void handle_test_args(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		// flags -d and -c to change dependencies and config directories
		if (std::string(argv[i]) == "-d") {
			if (i + 1 < argc) {
				DEPENDENCIES_DIR = argv[i + 1];
			}
		}
		if (std::string(argv[i]) == "-c") {
			if (i + 1 < argc) {
				CONFIG_DIR = argv[i + 1];
			}
		}
		// alternatively use -t to set test mode and change dirs automatically
		if (std::string(argv[i]) == "-t") {
			DEPENDENCIES_DIR = "dependencies";
			CONFIG_DIR = "config";
		}
	}
}

int main(int argc, char **argv) {

	handle_test_args(argc, argv);

	// init the boiler manager
	BoilerManager manager;
	manager.loadBoilers();

	if (argc < 2) {
		std::cerr << "error: No boilerplate name provided" << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
			std::cout << "usage: " << argv[0] << " <boilerplate-name>" << std::endl;
			return 0;
		}
		if (std::string(argv[i]) == "--list" || std::string(argv[i]) == "-l") {
			for (const Boiler& boiler : manager.getBoilers()) {
				std::cout << boiler.name() << std::endl;
			}
			return 0;
		}
		if (std::string(argv[i]) == "--init" || std::string(argv[i]) == "-i") {
			if (i + 1 < argc) {
				Boiler boiler = manager.findBoiler(argv[i + 1]);
				if (boiler.name() == "") {
					std::cerr << "error: Boilerplate not found" << std::endl;
					return 1;
				}
				std::cout << "boilerplate Found: " << boiler.name() << std::endl;
				// copy boilerplate to current directory
				std::string boilerDir = DEPENDENCIES_DIR + "/" + boiler.name();
				std::filesystem::copy(boilerDir, std::filesystem::current_path(), std::filesystem::copy_options::recursive);
				return 0;
			}
		}
	}

	return 0;
}
