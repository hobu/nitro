
include_directories(nrt/include)
include_directories(nitf/include)

if (WIN32)
      add_definitions("-DNRT_MODULE_EXPORTS=1")
      add_definitions("-DNITF_MODULE_EXPORTS=1")
endif()

add_sources(C_SOURCES nrt/source/*.c)
add_sources(C_SOURCES nitf/source/*.c)
add_sources(C_SOURCES nitf/shared/*.c)

add_library(${NITF_C_LIB_NAME} SHARED ${C_SOURCES})

install(TARGETS ${NITF_C_LIB_NAME}
  LIBRARY DESTINATION ${NITRO_LIB_SUBDIR}
)

