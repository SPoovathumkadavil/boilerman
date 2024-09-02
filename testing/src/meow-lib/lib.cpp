#include "lib.hpp"

library::library()
    : name {"meow"}
{
    feta::directories fetadir(name);
    project_directories = fetadir.proj_dirs();
}
