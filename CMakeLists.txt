cmake_minimum_required(VERSION 3.0)
include(ExternalProject)
project(picodeps CXX)

include_directories(include build/deps/json-master/src)

# Create libpicodeps.a
file(GLOB sources lib/*.cpp)
add_library(picodeps STATIC ${sources})

# Create picodeps
add_executable(picodeps_exe bin/picodeps.cpp)

# Libarchive
# TODO: libarchive actually has a CMakeLists.txt, use that
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

# Libressl
# TODO: don't need to build command line utilties
ExternalProject_Add(project_libressl
  PREFIX deps/libressl-2.1.6
  URL http://ftp.openbsd.org/pub/OpenBSD/LibreSSL/libressl-2.1.6.tar.gz
  CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
  BINARY_DIR deps/libressl-2.1.6/build
  INSTALL_DIR deps/libressl-2.1.6/build
)
add_dependencies(picodeps_exe project_libressl)
ExternalProject_Get_Property(project_libressl INSTALL_DIR)
target_link_libraries(picodeps_exe ${INSTALL_DIR}/lib/libcrypto.a ${INSTALL_DIR}/lib/libssl.a)

# Libcurl
# TODO: Get this to build in the prefix dir
set(libressl_install_dir ${INSTALL_DIR})
message("${libressl_install_dir}") #
ExternalProject_Add(project_libcurl
  DEPENDS project_libressl
  PREFIX deps/curl-7.42.1
  URL http://curl.haxx.se/download/curl-7.42.1.tar.gz
  CONFIGURE_COMMAND env PKG_CONFIG_PATH=${libressl_install_dir} <SOURCE_DIR>/configure --disable-shared --without-zlib --without-libidn --disable-ldap
  BINARY_DIR deps/curl-7.42.1/build
  INSTALL_DIR deps/curl-7.42.1/build
)
add_dependencies(picodeps_exe project_libcurl)
ExternalProject_Get_Property(project_libcurl INSTALL_DIR)
target_link_libraries(picodeps_exe ${INSTALL_DIR}/lib/libcurl.a)

target_link_libraries(picodeps_exe picodeps)
set_target_properties(picodeps_exe PROPERTIES OUTPUT_NAME "picodeps")
# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra --std=c++11")

