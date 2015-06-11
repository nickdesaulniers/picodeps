cmake_minimum_required(VERSION 3.0)
project(picodeps CXX)

include_directories(include build/deps/json-master/src)

# Create libpicodeps.a
file(GLOB sources lib/*.cpp)
add_library(picodeps STATIC ${sources})

# Create picodeps
add_executable(picodeps_exe bin/picodeps.cpp)

# TODO: libarchive actually has a CMakeLists.txt, use that
include(ExternalProject)
ExternalProject_Add(project_archive
  PREFIX deps/libarchive-3.1.2
  URL http://libarchive.org/downloads/libarchive-3.1.2.tar.gz
  CONFIGURE_COMMAND <SOURCE_DIR>/configure --without-zlib --without-bz2lib --without-lzmadec --without-iconv --without-lzma --without-lzo2 --without-nettle --without-openssl --without-xml2 --prefix=<INSTALL_DIR>
  BINARY_DIR deps/libarchive-3.1.2/build
  INSTALL_DIR deps/libarchive-3.1.2/build
)
add_dependencies(picodeps_exe project_archive)
ExternalProject_Get_Property(project_archive INSTALL_DIR)
target_link_libraries(picodeps_exe ${INSTALL_DIR}/lib/libarchive.a)

# Dependencies
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries#Using_external_libraries_that_CMake_doesn.27t_yet_have_modules_for
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
foreach(dependency curl crypto ssl)
  find_package(Lib${dependency} REQUIRED)
  if(NOT ${Lib${dependency}})
    message("Did you remember to run the bootstrap script?")
  endif()
  string(TOUPPER ${dependency} DEPENDENCY)
  include_directories(${LIB${DEPENDENCY}_INCLUDE_DIR})
  target_link_libraries(picodeps_exe picodeps ${LIB${DEPENDENCY}_LIBRARIES})
endforeach()

target_link_libraries(picodeps_exe picodeps)
set_target_properties(picodeps_exe PROPERTIES OUTPUT_NAME "picodeps")
# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra --std=c++11")

