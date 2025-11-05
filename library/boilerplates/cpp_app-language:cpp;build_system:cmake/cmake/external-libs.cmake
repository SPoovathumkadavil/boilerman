# -- local --

# find_package(fmt REQUIRED)
# message("-- Package \"fmt\" found: ${fmt_FOUND}")
# target_link_libraries(|||name||| fmt::fmt)

# -- remote --

include(FetchContent)

# ---- fmt ----
# FetchContent_Declare(
#   fmt
#   GIT_REPOSITORY https://github.com/fmtlib/fmt
#   GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
# FetchContent_MakeAvailable(fmt)
# target_link_libraries(|||name||| fmt::fmt)
