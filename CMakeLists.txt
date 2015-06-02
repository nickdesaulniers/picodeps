cmake_minimum_required(VERSION 3.0)

include_directories(include json/src)

# Create libpetablocks.a
file(GLOB sources lib/*.cpp)
add_library(petablocks STATIC ${sources})

# Create petablocks
add_executable(petablocks_exe bin/petablocks.cpp)

# Dependencies
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries#Using_external_libraries_that_CMake_doesn.27t_yet_have_modules_for
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
foreach(dependency archive curl)
  find_package(Lib${dependency} REQUIRED)
  string(TOUPPER ${dependency} DEPENDENCY)
  include_directories(${LIB${DEPENDENCY}_INCLUDE_DIR})
  target_link_libraries(petablocks_exe petablocks ${LIB${DEPENDENCY}_LIBRARIES})
endforeach()

set_target_properties(petablocks_exe PROPERTIES OUTPUT_NAME "petablocks")
# Compiler flags
add_definitions(-Wall -Wextra --std=c++11 -g)

