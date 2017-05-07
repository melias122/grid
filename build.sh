#!/bin/bash
set -e

CC=mpicc
CXX=mpicxx
BUILD_DIR=.build
BUILD=RelWithDebInfo  # Debug, Release, RelWithDebInfo
MODULES="cmake/3.1.0 gcc/5.4 mvapich2/2.2"

build_boost() {
    if [ ! -f vendor/.boost.lock ]; then
	scripts/build_boost.sh
    fi
}

create_project() {

    project_name=$1
    project_dir=project/$project_name

    # exit if project exists
    if [ -d $project_dir ]; then
	echo "$project_dir already exists"
	exit 1
    fi

    mkdir -pv $project_dir

    cat << EOF > $project_dir/main.cpp
#include <iostream>

#include "MpiApp.h"

using namespace std;

int main(int argc, char **argv)
{
    // MpiApp app(argc, argv);
    // const mpi::communicator &comm = app.communicator();

    return 0;
}
EOF

    cat << EOF > $project_dir/CMakeLists.txt
add_executable($project_name
    main.cpp

    # add additional .cpp files here
)

target_link_libraries($project_name grid)
install(TARGETS $project_name DESTINATION \${PROJECT_SOURCE_DIR}/$project_dir)
EOF

    cat << EOF > $project_dir/${project_name}.pbs
#!/bin/bash

#PBS -N $project_name
#PBS -A 3ANTAL-2016
#PBS -q parallel
#PBS -l nodes=1:ppn=1
#PBS -l walltime=240:00:00

#PBS -M xelias@stuba.sk
#PBS -m ea

. /etc/profile.d/modules.sh
module purge
module load $MODULES

CMD="mpirun ./$project_name"

# prechod do pracovneho priečinka
cd $project_dir

# spustenie ulohy
eval \$CMD
EOF

    echo "add_subdirectory($project_name)" >> project/CMakeLists.txt
}

clang_format_all() {
	if hash clang-format 2>/dev/null; then
		find src/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
		find project/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
	fi
}

load_modules() {
    if hash module 2>/dev/null; then
	module load $MODULES
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
	make -j $(nproc) install > /dev/null
}

usage() {
	echo "Usage: $0 [-b|--build] [-h|--help] [-r|--run bin/project_name] [-n|--new-project]"
	echo "   -b|--build:       builds whole project and binaries"
	echo "   -h|--help:        prints this help"
	echo "   -r|--run:         runs executable"
	echo "   -n|--new-project: creates new project from template"
	exit 1
}

# parsing options with getopt https://gist.github.com/cosimo/3760587
OPTS=`getopt -o hbr:n: --long help,build,run,new-project: -n $0 -- "$@"`
if [ $? != 0 ] ; then echo "Failed parsing options." >&2 ; exit 1 ; fi

# echo "$OPTS"
eval set -- "$OPTS"

while true; do
	case "$1" in
		-h | --help ) usage ;;
		-b | --build ) build $BUILD; shift ;;
		-r | --run ) echo todo ; shift ;;
		-n | --new-project ) create_project $2 ; shift ;;
		-- ) shift; break ;;
		* ) break ;;
	esac
done
