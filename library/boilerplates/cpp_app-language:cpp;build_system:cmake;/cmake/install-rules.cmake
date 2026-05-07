install(
    TARGETS |||target_name|||_exe
    RUNTIME COMPONENT |||target_name|||_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
