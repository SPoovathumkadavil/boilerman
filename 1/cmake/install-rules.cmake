if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/1-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package 1)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT 1_Development
)

install(
    TARGETS 1_1
    EXPORT 1Targets
    RUNTIME #
    COMPONENT 1_Runtime
    LIBRARY #
    COMPONENT 1_Runtime
    NAMELINK_COMPONENT 1_Development
    ARCHIVE #
    COMPONENT 1_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    1_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE 1_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(1_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${1_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT 1_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${1_INSTALL_CMAKEDIR}"
    COMPONENT 1_Development
)

install(
    EXPORT 1Targets
    NAMESPACE 1::
    DESTINATION "${1_INSTALL_CMAKEDIR}"
    COMPONENT 1_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
