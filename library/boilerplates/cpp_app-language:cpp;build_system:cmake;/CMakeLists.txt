cmake_minimum_required(VERSION 3.16)

include(cmake/prevent-build-in-source.cmake)

project(
    |||name|||
    VERSION 0.1.0
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)

# --- developer mode ---

# Developer mode enables targets and code paths in the CMake scripts that are
# only relevant for the developer(s) of project
# Targets necessary to build the project must be provided unconditionally, so
# consumers can trivially build and package the project
if(PROJECT_IS_TOP_LEVEL)
  option(|||name|||_DEVELOPER_MODE "Enable developer mode" OFF)
endif()

# --- warning guard ---

# target_include_directories with the SYSTEM modifier will request the compiler
# to omit warnings from the provided paths, if the compiler supports that
# This is to provide a user experience similar to find_package when
# add_subdirectory or FetchContent is used to consume this project
set(warning_guard "")
if(NOT PROJECT_IS_TOP_LEVEL)
  option(
    |||name|||_INCLUDES_WITH_SYSTEM
      "Use SYSTEM modifier for project's includes, disabling warnings"
      ON
  )
  mark_as_advanced(|||name|||_INCLUDES_WITH_SYSTEM)
  if(|||name|||_INCLUDES_WITH_SYSTEM)
    set(warning_guard SYSTEM)
  endif()
endif()

# --- source files ---

include(cmake/sources.cmake)
include(cmake/external-lib.cmake)

# --- install rules ---

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# --- developer mode ---

if(NOT |||name|||_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of project"
  )
endif()

include(cmake/dev-mode.cmake)
