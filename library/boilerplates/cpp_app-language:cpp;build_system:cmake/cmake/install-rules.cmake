install(
    TARGETS |||name|||_exe
    RUNTIME COMPONENT |||name|||_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
