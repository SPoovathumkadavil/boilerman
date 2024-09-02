# ---- local ----

find_package(fetalib REQUIRED)
message("-- Package \"fetalib\" found: ${fetalib_FOUND}")
target_link_libraries(meow_lib fetalib::fetalib)

# ---- remote ----

# include(FetchContent)

# ---- raylib ----
# FetchContent_Declare(
#     raylib
#     GIT_REPOSITORY https://github.com/raysan5/raylib.git
# )
# FetchContent_MakeAvailable(raylib)
# target_link_libraries(meow_lib raylib)

# ---- fmt ----
# FetchContent_Declare(
#   fmt
#   GIT_REPOSITORY https://github.com/fmtlib/fmt
#   GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
# FetchContent_MakeAvailable(fmt)
# target_link_libraries(meow_lib fmt::fmt)
