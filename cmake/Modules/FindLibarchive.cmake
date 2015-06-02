# Locate libarchive library
# This module defines
#  LIBARCHIVE_FOUND, if false, do not try to link to libuv
#  LIBARCHIVE_LIBRARIES
#  LIBARCHIVE_INCLUDE_DIR, where to find archive.h
#
# I build libarchive with:
# ../configure --without-zlib --without-bz2lib --without-lzmadec --without-iconv --without-lzma --without-lzo2 --without-nettle --without-openssl --without-xml2

FIND_PATH(LIBARCHIVE_INCLUDE_DIR archive.h PATHS libarchive-3.1.2/libarchive)
FIND_LIBRARY(LIBARCHIVE_LIBRARIES NAMES libarchive.a PATHS libarchive-3.1.2/build/.libs)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBARCHIVE DEFAULT_MSG LIBARCHIVE_LIBRARIES LIBARCHIVE_INCLUDE_DIR)
