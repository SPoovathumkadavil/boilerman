install(
    TARGETS boilerman_exe
    RUNTIME COMPONENT boilerman_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
