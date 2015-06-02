cmake_minimum_required(VERSION 3.0)
include_directories(include json/src curl-7.42.1 libarchive-3.1.2/libarchive)
# Create libpetablocks.a
add_library(petablocks STATIC lib/petablocks.cpp json/src/json.hpp
  lib/dependency.cpp lib/tarball.cpp)
# Create petablocks
add_executable(petablocks_exe bin/petablocks.cpp)
# Dependencies
## I build curl with:
## ../configure --without-ssl --disable-shared --without-zlib --without-libidn --disable-ldap
find_library(my_curl NAMES libcurl.a PATHS "curl-7.42.1/build/lib/.libs/")
message(${my_curl})
add_library(curl STATIC IMPORTED)
set_target_properties(curl PROPERTIES IMPORTED_LOCATION ${my_curl})

## I build libarchive with:
## ../configure --without-zlib --without-bz2lib --without-lzmadec --without-iconv --without-lzma --without-lzo2 --without-nettle --without-openssl --without-xml2
find_library(my_archive NAMES libarchive.a PATHS "libarchive-3.1.2/build/.libs/")
add_library(archive STATIC IMPORTED)
set_target_properties(archive PROPERTIES IMPORTED_LOCATION ${my_archive})
message(${my_archive})

target_link_libraries(petablocks_exe petablocks curl archive)
set_target_properties(petablocks_exe PROPERTIES OUTPUT_NAME "petablocks")
# Compiler flags
add_definitions(-Wall -Wextra --std=c++11 -g)

