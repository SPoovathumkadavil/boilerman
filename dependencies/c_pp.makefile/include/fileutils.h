
#ifndef fileutils_h
#define fileutils_h

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <filesystem>
#include <fstream>
#include <pwd.h>
#include <vector>

// get home directory
// if HOME environment variable is not set, getpwuid() is used to get the home directory
std::string get_home_dir() {
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL)
        homedir = getpwuid(getuid())->pw_dir;
    return std::string(homedir);
};

// get current working directory, this is the directory where the executable is run from
std::string get_current_dir() {
    return std::filesystem::current_path();
};

std::vector<std::string> get_files_in_dir(std::string dir) {
    std::vector<std::string> files;
    for (const auto & entry : std::filesystem::directory_iterator(dir)) {
        if (!std::filesystem::is_directory(entry.path())) {
            files.push_back(entry.path());
        }
    }
    return files;
};

std::vector<std::string> get_dirs_in_dir(std::string dir) {
    std::vector<std::string> dirs;
    for (const auto & entry : std::filesystem::directory_iterator(dir)) {
        if (std::filesystem::is_directory(entry.path())) {
            dirs.push_back(entry.path());
        }
    }
    return dirs;
};

std::vector<std::string> read_file(std::string filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
};

void write_file(std::string filename, std::vector<std::string> lines) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (std::string line : lines) {
            file << line << std::endl;
        }
        file.close();
    }
};

// read project.json for project name
const std::string HOME_DIR = get_home_dir();
const std::string PROJECT_NAME = "Boilerman";
std::string DEPENDENCIES_DIR = HOME_DIR + "/Documents/dev/.dependencies/" + PROJECT_NAME;
std::string CONFIG_DIR = HOME_DIR + "/Documents/dev/.config/" + PROJECT_NAME;

#endif
