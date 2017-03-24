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
	module load cmake/3.1.0
	module load gcc/6.3
	module load mvapich2/2.2
}

build_all() {
	clang_format_all
	load_modules
	mkdir -p $BUILD_DIR
	cd $BUILD_DIR
	cmake ..
	make -j $(nproc)
}

#run() {
#	./$BUILD_DIR/
#}

while getopts ":ar:" opt; do
	case "${opt}" in
		a) build_all
		   ;;
		r) run opt
		   ;;
		*) usage
		   ;;
	esac
done
shift $((OPTIND-1))

