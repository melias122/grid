#!/bin/bash

CXX=mpicxx

BUILD_DIR=build

mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake ..
make -j $(nproc)
