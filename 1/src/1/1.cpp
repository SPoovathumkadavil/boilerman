#include <string>

#include "1/1.hpp"

exported_class::exported_class()
    : m_name {"1"}
{
  feta::directories fetadir(m_name);
  project_directories = fetadir.proj_dirs();
}

auto exported_class::name() const -> char const*
{
  return m_name.c_str();
}
