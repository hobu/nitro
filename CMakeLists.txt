
cmake_minimum_required(VERSION 2.8.7)

project(Nitro)

set(CMAKE_COLOR_MAKEFILE ON)

macro (add_sources)
    
    file(GLOB_RECURSE FILES ${ARGN})
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${FILES})
        list (APPEND SRC "${_src}")
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (SRC ${SRC} PARENT_SCOPE)
    endif()
endmacro()

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Debug CACHE STRING 
  "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif()
message(STATUS "Setting Nitro build type - ${CMAKE_BUILD_TYPE}")



set(NITRO_BUILD_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Output directory in which to build RUNTIME target files.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${NITRO_BUILD_OUTPUT_DIRECTORY})

# Output directory in which to build LIBRARY target files
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${NITRO_BUILD_OUTPUT_DIRECTORY})

# Output directory in which to build ARCHIVE target files.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${NITRO_BUILD_OUTPUT_DIRECTORY}) 

set(DEFAULT_BIN_SUBDIR bin)
set(DEFAULT_LIB_SUBDIR lib)
set(DEFAULT_INCLUDE_SUBDIR include )
set(NITRO_BIN_SUBDIR ${DEFAULT_BIN_SUBDIR} CACHE STRING
  "Subdirectory where executables will be installed")
set(NITRO_LIB_SUBDIR ${DEFAULT_LIB_SUBDIR} CACHE STRING
  "Subdirectory where libraries will be installed")
set(NITRO_INCLUDE_SUBDIR ${DEFAULT_INCLUDE_SUBDIR} CACHE STRING
  "Subdirectory where header files will be installed")
set(NITRO_PKG_SUBDIR pkgconfig CACHE STRING
  "Subdirectory where pkgconfig will be installed")


set(NITF_C_LIB_NAME "nitf-c")
set(NITF_CPP_LIB_NAME "nitf-cpp")
add_subdirectory(c)
add_subdirectory(c++)





install(DIRECTORY "./c/nitf/include/"
  DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c/nrt/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/nitf/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/except/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/except/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/io/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/logging/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/mem/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/mt/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/str/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY "./c++/sys/include/"
DESTINATION ${NITRO_INCLUDE_SUBDIR}/nitro/c++
FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

set(PKGCFG_PREFIX "${CMAKE_INSTALL_PREFIX}")
set(PKGCFG_INC_DIR "${NITRO_INCLUDE_SUBDIR}")
set(PKGCFG_LIB_DIR "${NITRO_LIB_SUBDIR}")
set(PKGCFG_REQUIRES  "")
set(PKGCFG_VERSION ${VERSION})
set(PKGCFG_LINK_FLAGS "-lnitf-cpp -lnitf-c")
set(PKGCFG_COMPILE_FLAGS "")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libnitf.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/libnitf.pc @ONLY)
  
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libnitf.pc
  DESTINATION ${NITRO_PKG_SUBDIR}
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)