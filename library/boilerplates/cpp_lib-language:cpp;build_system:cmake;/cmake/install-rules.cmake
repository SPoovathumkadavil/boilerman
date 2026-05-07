include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  TARGETS |||target_name|||
  EXPORT |||target_name|||Targets
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
  DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
  EXPORT |||target_name|||Targets
  NAMESPACE |||target_name|||::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/|||target_name|||"
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
  "${PROJECT_BINARY_DIR}/|||target_name|||Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/|||target_name|||"
)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/|||target_name|||ConfigVersion.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
  "${PROJECT_BINARY_DIR}/|||target_name|||Config.cmake"
  "${PROJECT_BINARY_DIR}/|||target_name|||ConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/|||target_name|||"
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
