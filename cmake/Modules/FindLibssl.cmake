# Locate libressl library
# This module defines
#  LIBSSL_FOUND, if false, do not try to link to libcrypto
#  LIBSSL_INCLUDE_DIR, is not currently used
#  LIBSSL_LIBRARIES
#
# I build libressl with:
# ../configure --prefix=`pwd`

SET(LIBSSL_INCLUDE_DIR build/deps/libressl-2.1.6/include)
FIND_LIBRARY(LIBSSL_LIBRARIES NAMES libssl.a PATHS build/deps/libressl-2.1.6/build/ssl/.libs)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBSSL DEFAULT_MSG LIBSSL_LIBRARIES LIBSSL_INCLUDE_DIR)
