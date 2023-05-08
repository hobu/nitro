set(CMAKE_CXX_STANDARD 17)
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

add_sources(CPP_SOURCES nitf/source/*.cpp)
add_sources(CPP_SOURCES except/source/*.cpp)
add_sources(CPP_SOURCES import/source/*.cpp)
add_sources(CPP_SOURCES io/source/*.cpp)
add_sources(CPP_SOURCES logging/source/*.cpp)
add_sources(CPP_SOURCES mem/source/*.cpp)
add_sources(CPP_SOURCES mt/source/*.cpp)
add_sources(CPP_SOURCES str/source/*.cpp)
add_sources(CPP_SOURCES sys/source/*.cpp)

add_library(${NITF_CPP_LIB_NAME} SHARED ${CPP_SOURCES})

target_compile_options(${NITF_CPP_LIB_NAME} PUBLIC "--std=c++17")
target_link_libraries(${NITF_CPP_LIB_NAME} ${NITF_C_LIB_NAME} )
set_property(TARGET ${NITF_CPP_LIB_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${NITF_CPP_LIB_NAME} PROPERTY CXX_STANDARD_REQUIRED TRUE)

if (WIN32)
  target_link_libraries(${NITF_CPP_LIB_NAME} ws2_32)
endif()

install(TARGETS ${NITF_CPP_LIB_NAME}
    RUNTIME DESTINATION ${NITRO_BIN_SUBDIR}
    LIBRARY DESTINATION ${NITRO_LIB_SUBDIR}
    ARCHIVE DESTINATION ${NITRO_LIB_SUBDIR})

