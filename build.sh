#!/bin/bash
set -e

CC=mpicc
CXX=mpicxx
BUILD_DIR=_build
BUILD=Debug # or Release

build_boost() {
	if [ ! -f vendor/.boost.lock ]; then
		scripts/build_boost.sh
	fi
}

clang_format_all() {
	if hash clang-format 2>/dev/null; then
		find src/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
		find project/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
	fi
}

load_modules() {
	if hash module 2>/dev/null; then
		module load cmake/3.1.0 gcc/5.4 mvapich2/2.2
	fi
}

build() {
	load_modules
	build_boost
	clang_format_all
	mkdir -p $BUILD_DIR
	cd $BUILD_DIR

	cmake -DCMAKE_BUILD_TYPE=$1 ..
	make -j $(nproc)
}

usage() {
	echo "Usage: $0 [-b|--build] [-h|--help] [-r|--run bin/project_name]"
	echo "   -b|--build: builds whole project and binaries"
	echo "   -h|--help:  prints this help"
	echo "   -r|--run:   runs executable"
	exit 1
}

# parsing options with getopt https://gist.github.com/cosimo/3760587
OPTS=`getopt -o hbr: --long help,build,run: -n $0 -- "$@"`
if [ $? != 0 ] ; then echo "Failed parsing options." >&2 ; exit 1 ; fi

# echo "$OPTS"
eval set -- "$OPTS"

while true; do
	case "$1" in
		-h | --help ) usage ;;
		-b | --build ) build $BUILD; shift ;;
		-r | --run ) echo todo ; shift ;;
		-- ) shift; break ;;
		* ) break ;;
	esac
done
