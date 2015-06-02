mkdir -p build
curl -L https://github.com/nlohmann/json/archive/master.zip -O
unzip master.zip
mv json-master json

curl -O http://curl.haxx.se/download/curl-7.42.1.tar.gz
tar xvfz curl-7.42.1.tar.gz
cd curl-7.42.1
mkdir build
cd build
../configure --without-ssl --disable-shared --without-zlib --without-libidn --disable-ldap
make
cd ../..

curl -O http://libarchive.org/downloads/libarchive-3.1.2.tar.gz
tar xvfz libarchive-3.1.2.tar.gz
cd libarchive-3.1.2/build
../configure --without-zlib --without-bz2lib --without-lzmadec --without-iconv --without-lzma --without-lzo2 --without-nettle --without-openssl --without-xml2
make
cd ../..

cd build
cmake ..
make
