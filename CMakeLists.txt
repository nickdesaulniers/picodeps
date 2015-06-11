cmake_minimum_required(VERSION 3.0)
project(picodeps CXX)

include_directories(include build/deps/json-master/src)

# Create libpicodeps.a
file(GLOB sources lib/*.cpp)
add_library(picodeps STATIC ${sources})

# Create picodeps
add_executable(picodeps_exe bin/picodeps.cpp)

# Dependencies
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries#Using_external_libraries_that_CMake_doesn.27t_yet_have_modules_for
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
foreach(dependency archive curl crypto ssl)
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

