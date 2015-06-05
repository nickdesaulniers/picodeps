cd build/deps

# nlohman/json

# libressl
# openssl is insane, do not use, prefer libressl
cd libressl-2.1.6
mkdir build
cd build
../configure --prefix=`pwd`
make install
cd ../..

# libcurl
cd curl-7.42.1
mkdir build
cd build
PKG_CONFIG_PATH=../../libressl-2.1.6/build ../configure --disable-shared --without-zlib --without-libidn --disable-ldap
make
cd ../..

# libarchive
cd libarchive-3.1.2/build
../configure --without-zlib --without-bz2lib --without-lzmadec --without-iconv --without-lzma --without-lzo2 --without-nettle --without-openssl --without-xml2
make
cd ../../..

cmake ..
make
