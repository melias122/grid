#!/bin/bash
set -e

CC=mpicc
CXX=mpicxx
BUILD_DIR=release

usage() {
	echo "Usage: $0 [-a] [-r project]" 1>&2
	echo "   -a: builds all projects" 1>&2
	echo "   -r: runs project" 1>&2
	exit 1
}

build_boost() {
	if [ ! -f vendor/.boost.lock ]; then
		scripts/build_boost.sh
	fi
}

clang_format_all() {
	find src/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
	find project/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
}

load_modules() {
	if hash module 2>/dev/null; then
		module load cmake/3.1.0
		module load gcc/6.3
		module load mvapich2/2.2
	fi
}

build_all() {
	load_modules
	build_boost
	clang_format_all
	mkdir -p $BUILD_DIR
	cd $BUILD_DIR
	cmake ..
	make -j $(nproc)
}


#run() {
#}

while getopts ":adr:" opt; do
	case "${opt}" in
		a) build_all
		   ;;
#		r) run opt
#		   ;;
		*) usage
		   ;;
	esac
done
shift $((OPTIND-1))

