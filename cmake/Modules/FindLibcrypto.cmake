# Locate libressl library
# This module defines
#  LIBCRYPTO_FOUND, if false, do not try to link to libcrypto
#  LIBCRYPTO_INCLUDE_DIR, is not currently used
#  LIBCRYPTO_LIBRARIES
#
# I build libressl with:
# ../configure --prefix=`pwd`

SET(LIBCRYPTO_INCLUDE_DIR build/deps/libressl-2.1.6/include)
FIND_LIBRARY(LIBCRYPTO_LIBRARIES NAMES libcrypto.a PATHS build/deps/libressl-2.1.6/build/crypto/.libs)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBCRYPTO DEFAULT_MSG LIBCRYPTO_LIBRARIES LIBCRYPTO_INCLUDE_DIR)
