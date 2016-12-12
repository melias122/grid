cmake_minimum_required(VERSION 3.1.0)

project(grid CXX)

set(CMAKE_CXX_COMPILER mpic++)
set(CMAKE_CXX_STANDARD 11)

find_package(MPI REQUIRED)
if(NOT MPI_FOUND)
	message(FATAL_ERROR "Package MPI not found")
endif(NOT MPI_FOUND)

include_directories(SYSTEM
	${MPI_INCLUDE_PATH}
	src
)

add_subdirectory(example)
add_subdirectory(src)
