cmake_minimum_required(VERSION 3.0)
include_directories(include json/src)

# Create libpetablocks.a
file(GLOB sources lib/*.cpp)
add_library(petablocks STATIC ${sources})

# Dependencies
function(statically_link lib_name link_path include_path)
  find_library(my_${lib_name} NAMES lib${lib_name}.a PATHS ${link_path})
  message(${my_${lib_name}})
  add_library(${lib_name} STATIC IMPORTED)
  set_target_properties(${lib_name} PROPERTIES IMPORTED_LOCATION ${my_${lib_name}})
  include_directories(${include_path})
endfunction()
## I build curl with:
## ../configure --without-ssl --disable-shared --without-zlib --without-libidn --disable-ldap
## I build libarchive with:
## ../configure --without-zlib --without-bz2lib --without-lzmadec --without-iconv --without-lzma --without-lzo2 --without-nettle --without-openssl --without-xml2
statically_link(curl curl-7.42.1/build/lib/.libs curl-7.42.1)
statically_link(archive libarchive-3.1.2/build/.libs libarchive-3.1.2/libarchive)

# Create petablocks
add_executable(petablocks_exe bin/petablocks.cpp)
target_link_libraries(petablocks_exe petablocks curl archive)
set_target_properties(petablocks_exe PROPERTIES OUTPUT_NAME "petablocks")
# Compiler flags
add_definitions(-Wall -Wextra --std=c++11 -g)

