#!/bin/bash
set -e

CC=mpicc
CXX=mpicxx
BUILD_DIR=.build
BUILD=RelWithDebInfo  # Debug, Release, RelWithDebInfo
MODULES="cmake/3.1.0 gcc/5.4 mvapich2/2.2"

# every project needs id
if [ ! -s .project-id ]; then
    echo "please create .project-id. Run \"echo your-project-id > .project-id\""
    exit 1
fi

build_boost() {
    if [ ! -f vendor/.boost.lock ]; then
	scripts/build_boost.sh
    fi
}

create_project() {

    name=$(basename $1)
    dir=project/$name
    src=$dir/src

    # exit if project exists
    if [ -d $dir ]; then
	echo "$dir already exists"
	exit 1
    fi

    echo "creating new project $name"

    # create project and src directories
    mkdir -p $src

    # create main.cpp
    cat << EOF > $src/main.cpp
#include <iostream>

#include "MpiApp.h"

// nodes defines number of nodes to use
// ppn defines number of proccesors to use
// total cores = nodes * ppn
#define nodes 1
#define ppn 1

using namespace std;

int main(int argc, char **argv)
{
    MpiApp app(argc, argv);
    cout << "Hello, grid" << endl;
    return 0;
}
EOF

    # register project
    echo "add_subdirectory($name)" >> project/CMakeLists.txt

    # crate project CMakeLists
    cat << EOF > $dir/CMakeLists.txt
add_executable($name
    src/main.cpp

    # add additional .cpp files here
)

target_link_libraries($name grid)
install(TARGETS $name DESTINATION \${PROJECT_SOURCE_DIR}/$dir)
EOF

    cat << EOF > $dir/${name}.pbs
#!/bin/bash

#PBS -N $name
#PBS -A $(cat .project-id)
#PBS -q parallel
#PBS -l nodes=1:ppn=1
#PBS -l walltime=240:00:00

. /etc/profile.d/modules.sh
module purge
module load $MODULES

CMD="mpirun ./$name"

# prechod do priečinka s programom (project/$name)
cd \$PBS_O_WORKDIR

# spustenie ulohy
eval \$CMD
EOF

    # add binary file to .gitignore
    cat << EOF > $dir/.gitignore
$name
EOF
}

run_project() {

    # project we want to run
    name=$(basename $1)
    rpath=project/$name
    apath=$(pwd)/$rpath
    pbsf=$rpath/${name}.pbs
    main=$rpath/src/main.cpp
    isnum='^[0-9]+$'

    if [ ! -d $rpath ]; then
	echo "$rpath does not exist (are you in project root directory?)"
	exit 1
    fi

    if ! type $rpath/$name 2>/dev/null 1>/dev/null; then
	echo "$rpath/$name does not exist (did you run ./build.sh -b?)"
	exit 1
    fi

    if [ ! -f $pbsf ]; then
	echo "$pbsf does not exist"
	exit 1
    fi

    # check how many nodes and cores are specified by main
    if [ -f $main ]; then
	nodes=$(grep "#define nodes" $rpath/src/main.cpp | cut -d' ' -f 3)
	ppn=$(grep "#define ppn" $rpath/src/main.cpp | cut -d' ' -f 3)
    fi

    # check if they are realy numbers
    if ! [[ $nodes =~ $isnum ]]; then
	echo "please add \"#define Nodes number\" to $main"
	exit 1
    fi

    if ! [[ $ppn =~ $isnum ]]; then
	echo "please add \"#define Procs number\" to $main"
	exit 1
    fi

    # replace old nodes and ppn in .pbs
    old_nodes=$(grep "nodes" $pbsf | cut -d' ' -f3 | cut -d: -f1 | cut -d= -f2)
    old_ppn=$(grep "ppn" $pbsf | cut -d' ' -f3 | cut -d: -f2 | cut -d= -f2)
    sed -i 's/nodes=$old_nodes/nodes=$nodes/' $pbsf
    sed -i 's/ppn=$old_ppn/ppn=$ppn/' $pbsf

    # if we are on hpc.stuba.sk
    if hash qsub 2>/dev/null; then
        # use current .project-id
	sed -i 's/^#PBS -A.*/#PBS -A $(cat .project-id)/' $pbsf
	qsub -d $apath $pbsf
	echo "project: $name $(cat .project-id) added to queue (check with: qstat -u $USER)"
    else
	# we are running local machine
	pushd $rpath 1>/dev/null
	mpirun -n $(( $nodes * $ppn )) ./$name
	popd 1>/dev/null
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
	echo "Usage: $0 [-b|--build] [-h|--help] [-r|--run project_name] [-n|--new-project]"
	echo "   -b|--build:       builds whole project and binaries"
	echo "   -h|--help:        prints this help"
	echo "   -r|--run:         adds project to queue (path must be relative and from root of this project)"
	echo "   -n|--new-project: creates new project from template"
	echo ""
	echo "Current project is: $(cat .project-id)"
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
		-r | --run ) run_project $2 ; shift ;;
		-n | --new-project ) create_project $2 ; shift ;;
		-- ) shift; break ;;
		* ) break ;;
	esac
done
