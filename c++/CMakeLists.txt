include_directories(nitf/include)
include_directories(${PROJECT_SOURCE_DIR}/c/nitf/include)
include_directories(${PROJECT_SOURCE_DIR}/c/nrt/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/except/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/io/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/import/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/logging/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/mem/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/mt/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/str/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/sys/include)

add_definitions("-D_REENTRANT")
if (NOT WIN32)
add_definitions("-D__POSIX")
else()

endif()

if (WIN32)
      add_definitions("-DNRT_MODULE_EXPORTS=1")
      add_definitions("-DNITF_MODULE_EXPORTS=1")
endif()

add_sources(nitf/source/*.cpp)
add_sources(except/source/*.cpp)
add_sources(import/source/*.cpp)
add_sources(io/source/*.cpp)
add_sources(logging/source/*.cpp)
add_sources(mem/source/*.cpp)
add_sources(mt/source/*.cpp)
add_sources(str/source/*.cpp)
add_sources(sys/source/*.cpp)

add_library(${NITF_CPP_LIB_NAME} SHARED ${SRC})

target_link_libraries(${NITF_CPP_LIB_NAME} ${NITF_C_LIB_NAME} )

if (WIN32)
  target_link_libraries(${NITF_CPP_LIB_NAME} ws2_32)
endif()

install(TARGETS ${NITF_CPP_LIB_NAME}
    RUNTIME DESTINATION ${NITRO_BIN_SUBDIR}
    LIBRARY DESTINATION ${NITRO_LIB_SUBDIR}
    ARCHIVE DESTINATION ${NITRO_LIB_SUBDIR})

