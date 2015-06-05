mkdir -p build/deps
cd build/deps

# nlohman/json
curl -L https://github.com/nlohmann/json/archive/master.zip -O
unzip master.zip
rm master.zip

# libressl
# openssl is insane, do not use, prefer libressl
curl -O http://ftp.openbsd.org/pub/OpenBSD/LibreSSL/libressl-2.1.6.tar.gz
tar xvfz libressl-2.1.6.tar.gz
rm libressl-2.1.6.tar.gz
cd libressl-2.1.6
mkdir build
cd build
../configure --prefix=`pwd`
make install
cd ../..

# libcurl
curl -O http://curl.haxx.se/download/curl-7.42.1.tar.gz
tar xvfz curl-7.42.1.tar.gz
rm curl-7.42.1.tar.gz
cd curl-7.42.1
mkdir build
cd build
PKG_CONFIG_PATH=../../libressl-2.1.6/build ../configure --disable-shared --without-zlib --without-libidn --disable-ldap
make
cd ../..

# libarchive
curl -O http://libarchive.org/downloads/libarchive-3.1.2.tar.gz
tar xvfz libarchive-3.1.2.tar.gz
rm libarchive-3.1.2.tar.gz
cd libarchive-3.1.2/build
../configure --without-zlib --without-bz2lib --without-lzmadec --without-iconv --without-lzma --without-lzo2 --without-nettle --without-openssl --without-xml2
make
cd ../../..

cmake ..
make
