install(
    TARGETS meow_exe
    RUNTIME COMPONENT meow_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
