
cmake_minimum_required(VERSION 3.5)

project(Nitro)

set(CMAKE_COLOR_MAKEFILE ON)

set(CMAKE_C_STANDARD 90)
set(C_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

macro (add_sources _varlist )

    file(GLOB_RECURSE FILES ${ARGN} )
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${FILES})
        list (APPEND ${_varlist} "${_src}")
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (${ARGV1} ${ARGV1} PARENT_SCOPE)
    endif()
endmacro()

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


# note we default to debug mode
if(NOT MSVC_IDE)
  if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel" FORCE)
  endif()
  message(STATUS "Setting Nitro build type - ${CMAKE_BUILD_TYPE}")
endif()

set(NITRO_BUILD_TYPE ${CMAKE_BUILD_TYPE})

# TODO: Still testing the output paths --mloskot
set(NITRO_BUILD_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Output directory in which to build RUNTIME target files.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${NITRO_BUILD_OUTPUT_DIRECTORY})

# Output directory in which to build LIBRARY target files
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${NITRO_BUILD_OUTPUT_DIRECTORY})

# Output directory in which to build ARCHIVE target files.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${NITRO_BUILD_OUTPUT_DIRECTORY})


#------------------------------------------------------------------------------
# Platform and compiler specific settings
#------------------------------------------------------------------------------

if(WIN32)
  if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_WARNING)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-DNITF_MODULE_EXPORTS)
    add_definitions(-DSIZEOF_SIZE_T=8)
    add_definitions(-DWIN32)
    add_definitions(-DNOMINMAX)
    add_definitions(/wd4290)
    add_definitions(/GR)
    add_definitions(/EHs)

    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
      string(REGEX REPLACE "/W[0-4]" "/W4"
        CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()

    if(MSVC90 OR MSVC10 OR MSVC11)
      if (NOT ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION} LESS 2.8.6)
        include(ProcessorCount)
        ProcessorCount(N)
        if(NOT N EQUAL 0)
          set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   /MP${N}")
  	      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP${N}")
        endif()
      endif()
    endif()
  endif(MSVC)
endif()

cmake_policy(SET CMP0042 NEW) # osx rpath
set(CMAKE_INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/${NITRO_LIB_SUBDIR})

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
