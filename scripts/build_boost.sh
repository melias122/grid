#!/bin/bash
set -e

mkdir -p vendor/
wget --no-check-certificate https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.bz2 -O vendor/boost_1_63_0.tar.bz2
echo "extracting boost"
tar -xjf vendor/boost_1_63_0.tar.bz2 -C vendor/
pushd vendor/boost_1_63_0
./bootstrap.sh --without-libraries=python
echo 'using mpi ;' >> project-config.jam
./b2 --with-mpi --with-serialization -j `nproc`
popd
touch vendor/.boost.lock
