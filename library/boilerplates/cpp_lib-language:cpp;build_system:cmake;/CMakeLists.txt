cmake_minimum_required(VERSION 3.16)

include(cmake/prevent-build-in-source.cmake)

project(
    |||target_name|||
    VERSION 0.1.0
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)

if(PROJECT_IS_TOP_LEVEL)
  option(|||cpp_name|||_DEVELOPER_MODE "Enable developer mode" OFF)
endif()

set(warning_guard "")
if(NOT PROJECT_IS_TOP_LEVEL)
  option(
    |||cpp_name|||_INCLUDES_WITH_SYSTEM
    "Use SYSTEM modifier for project's includes, disabling warnings"
    ON
  )
  mark_as_advanced(|||cpp_name|||_INCLUDES_WITH_SYSTEM)
  if(|||cpp_name|||_INCLUDES_WITH_SYSTEM)
    set(warning_guard SYSTEM)
  endif()
endif()

include(cmake/sources.cmake)
include(cmake/external-lib.cmake)

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

if(NOT |||cpp_name|||_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(AUTHOR_WARNING "Developer mode is intended for project maintainers")
endif()

include(cmake/dev-mode.cmake)
