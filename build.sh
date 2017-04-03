#!/bin/bash
set -e

CC=mpicc
CXX=mpicxx
BUILD_DIR=_build

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
	if hash clang-format 2>/dev/null; then
		find src/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
		find project/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
	fi
}

load_modules() {
	if hash module 2>/dev/null; then
		module load cmake/3.1.0
		module load gcc/5.4
		module load mvapich2/2.2
	fi
}

build_debug() {
	load_modules
	build_boost
	clang_format_all
	mkdir -p $BUILD_DIR
	cd $BUILD_DIR

#	cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -j $(nproc)
}


#run() {
#}

while getopts ":adr:" opt; do
	case "${opt}" in
		a) build_debug
		   ;;
#		r) run opt
#		   ;;
		*) usage
		   ;;
	esac
done
shift $((OPTIND-1))

