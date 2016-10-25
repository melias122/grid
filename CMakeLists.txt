cmake_minimum_required(VERSION 3.1.0)

project(grid C CXX)

set(CMAKE_CXX_COMPILER mpic++)

find_package(MPI REQUIRED)
if(NOT MPI_FOUND)
	message(FATAL_ERROR "Package MPI not found")
endif(NOT MPI_FOUND)

include_directories(SYSTEM
	${MPI_INCLUDE_PATH}
)

add_subdirectory(example)
