#!/bin/bash

CXX=mpicxx
BUILD_DIR=build

usage() {
	echo "Usage: $0 [-a] [-r project]" 1>&2
	echo "   -a: builds all projects" 1>&2
	echo "   -r: runs project" 1>&2
	exit 1
}

build_all() {
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

