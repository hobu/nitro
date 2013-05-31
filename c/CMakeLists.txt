
include_directories(nrt/include)
include_directories(nitf/include)

add_sources(nrt/source/*.c)
add_sources(nitf/source/*.c)

add_library(${NITF_C_LIB_NAME} SHARED ${SRC})

install(TARGETS ${NITF_C_LIB_NAME}
  RUNTIME DESTINATION ${NITRO_BIN_SUBDIR}
  LIBRARY DESTINATION ${NITRO_LIB_SUBDIR}
  ARCHIVE DESTINATION ${NITRO_LIB_SUBDIR})


