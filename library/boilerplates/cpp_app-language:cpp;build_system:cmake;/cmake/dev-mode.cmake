include(cmake/folders.cmake)
include(CTest)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

add_custom_target(
    run-exe
    COMMAND |||target_name|||_exe
    VERBATIM
)
add_dependencies(run-exe |||target_name|||_exe)

option(BUILD_MCSS_DOCS "Build documentation using Doxygen and m.css" OFF)
if(BUILD_MCSS_DOCS)
  include(cmake/docs.cmake)
endif()

add_folders(Project)
