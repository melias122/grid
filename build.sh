#!/bin/bash

CC=mpicc
CXX=mpicxx
BUILD_DIR=build

usage() {
	echo "Usage: $0 [-a] [-r project]" 1>&2
	echo "   -a: builds all projects" 1>&2
	echo "   -r: runs project" 1>&2
	exit 1
}

clang_format_all() {
	find . \
		 -name '*.h' \
		 -o -name '*.cpp' \
		| xargs clang-format -i -style=Webkit
}

load_modules() {
	if hash module 2>/dev/null; then
		module load cmake/3.1.0
		module load gcc/6.3
		module load mvapich2/2.2
	fi
}

build_debug() {
	clang_format_all
	load_modules
	mkdir -p debug
	cd debug
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -j $(nproc)
}

build_release() {
	clang_format_all
	load_modules
	mkdir -p release
	cd release
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make -j $(nproc)
}


#run() {
#}

while getopts ":adr:" opt; do
	case "${opt}" in
		a) build_release
		   ;;
		d) build_debug
		   ;;
#		r) run opt
#		   ;;
		*) usage
		   ;;
	esac
done
shift $((OPTIND-1))

