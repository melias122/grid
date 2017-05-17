#!/bin/bash
set -e

CC=mpicc
CXX=mpicxx
BUILD_DIR=.build
BUILD=RelWithDebInfo  # Debug, Release, RelWithDebInfo
MODULES="cmake/3.1.0 gcc/5.4 mvapich2/2.2"

# every project needs id
if [ ! -s .project-id ]; then
    echo "please create .project-id file with project id from hpc.stuba.sk"
    echo "run folowing: echo \"project-id\" > .project-id"
    exit 1
fi

PROJECT_ID=$(grep "\w" .project-id | tr -d ' ')

build_boost() {
    if [ ! -f vendor/.boost.lock ]; then
	boost=boost_1_63_0.tar.bz2
	
	mkdir -p vendor/
	wget --no-check-certificate https://sourceforge.net/projects/boost/files/boost/1.63.0/$boost -O vendor/$boost

	echo "extracting boost"
	tar -xjf vendor/$boost -C vendor/

	# cd to boost
	pushd vendor/boost_1_63_0

	# setup
	./bootstrap.sh --without-libraries=python
	echo 'using mpi ;' >> project-config.jam
	./b2 --with-mpi --with-serialization -j `nproc`
	popd

	# create lock file
	touch vendor/.boost.lock

	# cleanup
	rm $boost
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

    echo "creating $dir"

    # create project and src directories
    mkdir -p $src

    # create main.cpp
    # TODO: add gpus support
    cat << EOF > $src/main.cpp
// Project $name
//
// nodes defines number of nodes to use
// ppn defines number of proccesors to use
// total cores = nodes * ppn
// nodes = 1
// ppn = 2
//
// queue defines queue for this project
// available queues are: serial, parallel, debug, gpu
// queue = parallel
//
// walltime defines time to run on grid. Format is hh:mm:ss
// walltime = 24:00:00
//
// Above variables are used for ../${name}.pbs
// Edit them as needed, but do not delete them!
// Notice that gpus are not supported yet.

#include <iostream>

#include "mpi/App.h"
#include "utils/Debug.h"

using namespace std;

int main(int argc, char **argv)
{
    MpiApp app(argc, argv);
    println("Hello, " << "MpiApp");
    return 0;
}
EOF

    # register project
    echo "add_subdirectory($name)" >> project/CMakeLists.txt

    # create project CMakeLists.txt
    cat << EOF > $dir/CMakeLists.txt
add_executable($name
    src/main.cpp

    # add more .cpp files here
    # src/file.cpp
)

target_link_libraries($name 
    libMpi
    
    # add more libs here
    # libPGA, libCipher, libFitness, ...
)
install(TARGETS $name DESTINATION \${PROJECT_SOURCE_DIR}/$dir)
EOF

    cat << EOF > $dir/${name}.pbs
#!/bin/bash

#PBS -N $name
#PBS -A $PROJECT_ID
#PBS -q parallel
#PBS -l nodes=1:ppn=1
#PBS -l walltime=24:00:00

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

    if [ ! -f $pbsf ]; then
	echo "$pbsf does not exist"
	exit 1
    fi

    # check how many nodes and cores are specified by main
    if [ -f $main ]; then
	nodes=$(sed 's/ //g' $main | grep '//nodes=' | cut -d= -f2)
	ppn=$(sed 's/ //g' $main | grep '//ppn=' | cut -d= -f2)
	queue=$(sed 's/ //g' $main | grep '//queue=' | cut -d= -f2)
	walltime=$(sed 's/ //g' $main | grep '//walltime=' | cut -d= -f2)


	if [ ! -z "$nodes" ]; then
	    # check if they are realy numbers
	    if ! [[ $nodes =~ $isnum ]]; then
		echo "please add // nodes=x to $main"
		exit 1
	    fi

	    # replace nodes in .pbs
	    old_nodes=$(grep "nodes" $pbsf | cut -d' ' -f3 | cut -d: -f1 | cut -d= -f2)
	    sed -i "s/nodes=${old_nodes}/nodes=${nodes}/g" $pbsf
	fi

	if [ ! -z "$ppn" ]; then
	    if ! [[ $ppn =~ $isnum ]]; then
		echo "please add // ppn=x to $main"
		exit 1
	    fi

	    # replace ppn in .pbs
	    old_ppn=$(grep "ppn" $pbsf | cut -d' ' -f3 | cut -d: -f2 | cut -d= -f2)
	    sed -i "s/ppn=${old_ppn}/ppn=${ppn}/g" $pbsf
	fi

	if [ ! -z "$queue" ]; then
	    # replace queue in .pbs
	    old_queue=$(grep "^#PBS -q" $pbsf | cut -d' ' -f3)
	    sed -i "s/^#PBS -q ${old_queue}/#PBS -q ${queue}/g" $pbsf
	fi

	if [ ! -z "$walltime" ]; then
	    # replace old walltime
	    old_walltime=$(grep "^#PBS -l walltime=" $pbsf | cut -d= -f2)
	    sed -i "s/walltime=${old_walltime}/walltime=${walltime}/g" $pbsf
	fi
    fi

    # rebuild project
    build

    # if we are on hpc.stuba.sk
    if hash qsub 2>/dev/null; then
        # use current .project-id in .pbs file
	sed -i "s/^#PBS -A.*/#PBS -A ${PROJECT_ID}/" $pbsf
	qsub -d $apath $pbsf
	echo "project: $name $PROJECT_ID added to queue (check with: qstat -u $USER)"
    else
	if [ -z "$nodes" ]; then
	    nodes=$(grep "nodes" $pbsf | cut -d' ' -f3 | cut -d: -f1 | cut -d= -f2)
	fi

	if [ -z "$ppn" ]; then
	    ppn=$(grep "ppn" $pbsf | cut -d' ' -f3 | cut -d: -f2 | cut -d= -f2)
	fi

	# we are running local machine
	pushd $rpath > /dev/null
	mpirun -n $(( $nodes * $ppn )) ./$name
	popd > /dev/null
    fi
}

clang_format_all() {
	if hash clang-format 2>/dev/null; then
		find module/ -name '*.h' -o -name '*.cpp' | xargs clang-format -i -style=file
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
	pushd $BUILD_DIR > /dev/null

	cmake -DCMAKE_BUILD_TYPE=$1 ..
	make -j $(nproc)
	make -j $(nproc) install > /dev/null
	popd > /dev/null
}

sync() {
    if [ ! -s .username ]; then
	echo "please create .username file with username you login to login.hpc.stuba.sk"
	echo "run folowing: echo \"username\" > .username"
	exit 1
    fi
    # get username a name of dir
    user=$(grep "\w" .username | tr -d ' ')
    dir=/work/${user}/$(basename $(pwd))

    # push this directory to grid
    rsync -av --include='.project-id' --include='.gitignore' --filter=':- .gitignore' --exclude='.*' ./ ${user}@login.hpc.stuba.sk:${dir}

    # pull changes from grid
    rsync -av --filter=':- .gitignore' --exclude='.*' ${user}@login.hpc.stuba.sk:${dir}/ .
}

usage() {
	echo "Usage: $0 [-b|--build] [-h|--help] [-r|--run project_name] [-n|--new-project]"
	echo "   -b|--build:       builds whole project and binaries"
	echo "   -h|--help:        prints this help"
	echo "   -r|--run:         adds project to queue (path must be relative and from root of this project)"
	echo "   -n|--new-project: creates new project from template"
	echo "   --sync:           synhronizes this project with hpc.stuba.sk"
	echo ""
	echo "Current project is: $PROJECT_ID"
	exit 1
}

# parsing options with getopt https://gist.github.com/cosimo/3760587
OPTS=`getopt -o hbr:n: --long help,build,run:,new-project:,sync,args: -n $0 -- "$@"`
if [ $? != 0 ] ; then echo "Failed parsing options." >&2 ; exit 1 ; fi

# echo $OPTS
eval set -- "$OPTS"
while true; do
	case "$1" in
		-h | --help ) usage ;;
		-b | --build ) build $BUILD; shift ;;
		--sync ) sync; shift ;;

		# TODO: add argument passing
		# --args )
		-r | --run ) run_project $2 ; shift ;; 
		-n | --new-project ) create_project $2 ; shift ;;
		-- ) shift; break ;;
		* ) break ;;
	esac
done
