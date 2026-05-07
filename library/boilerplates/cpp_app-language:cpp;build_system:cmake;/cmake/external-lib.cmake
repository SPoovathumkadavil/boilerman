
# --- local ---

# find_package(fetalib REQUIRED)
# message("-- Package \"fetalib\" found: ${fetalib_FOUND}")
# target_link_libraries(|||target_name|||_exe PRIVATE fetalib::files)

# --- remote ---

# include(FetchContent)
#
# FetchContent_Declare(
#   fetalib
#   GIT_REPOSITORY https://github.com/SPoovathumkadavil/fetalib.git
#   GIT_TAG v0.2
# )
# FetchContent_MakeAvailable(fetalib)
# target_link_libraries(|||target_name|||_exe PRIVATE fetalib::files)
