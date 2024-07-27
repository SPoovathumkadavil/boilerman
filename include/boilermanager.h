#ifndef boilermanager_h
#define boilermanager_h

#include "boiler.h"
#include <vector>

class BoilerManager {
public:
    void loadBoilers();
    Boiler findBoiler(const std::string& name);
    std::vector<Boiler> getBoilers() const;
private:
    std::vector<Boiler> boilers;
};

void handle_test_args(int argc, char *argv[]);
int main(int argc, char **argv);

#endif
