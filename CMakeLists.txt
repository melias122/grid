cmake_minimum_required(VERSION 3.1.0)

project(grid CXX)

set(CMAKE_CXX_COMPILER mpic++)
set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

find_package(MPI REQUIRED)
if(NOT MPI_FOUND)
	message(FATAL_ERROR "Package MPI not found")
endif(NOT MPI_FOUND)

include_directories(SYSTEM
	${MPI_INCLUDE_PATH}
	src
	src/PGA
)

add_subdirectory(src)
add_subdirectory(project)

