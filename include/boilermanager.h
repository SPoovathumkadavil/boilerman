#ifndef boilermanager_h
#define boilermanager_h

#include "boiler.h"
#include <vector>
#include <filesystem>

class BoilerManager {
public:
    void loadBoilers();
    Boiler findBoiler(const std::string& name);
    std::vector<Boiler> getBoilers() const;
private:
    std::vector<Boiler> boilers;
};

void recursive_resolve_copy(std::filesystem::path input_dir_path, std::filesystem::path output_dir_path, std::string name);
void handle_test_args(int argc, char *argv[]);
int main(int argc, char **argv);

#endif
