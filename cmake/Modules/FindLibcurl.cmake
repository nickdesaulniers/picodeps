# Locate libcurl library
# This module defines
#  LIBCURL_FOUND, if false, do not try to link to libuv
#  LIBCURL_LIBRARIES
#  LIBCURL_INCLUDE_DIR, where to find curl/curl.h
#
# I build curl with:
# ../configure --without-ssl --disable-shared --without-zlib --without-libidn --disable-ldap

FIND_PATH(LIBCURL_INCLUDE_DIR curl.h PATHS build/deps/curl-7.42.1/include/curl)
FIND_LIBRARY(LIBCURL_LIBRARIES NAMES libcurl.a PATHS build/deps/curl-7.42.1/build/lib/.libs)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBCURL DEFAULT_MSG LIBCURL_LIBRARIES LIBCURL_INCLUDE_DIR)
