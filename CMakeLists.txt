cmake_minimum_required(VERSION 3.1.0)

project(grid CXX)

set(CMAKE_CXX_COMPILER mpic++)
set(CMAKE_CXX_STANDARD 14)

find_package(MPI REQUIRED)
if(NOT MPI_FOUND)
	message(FATAL_ERROR "Package MPI not found")
endif(NOT MPI_FOUND)

set(BOOST_ROOT "vendor/boost_1_63_0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(BOOST_ALL_DYN_LINK OFF)

find_package(Boost 1.63.0 REQUIRED COMPONENTS mpi serialization)
IF(NOT Boost_FOUND)
	message(FATAL_ERROR "Package boost not found")
endif()

include_directories(
	${Boost_INCLUDE_DIR}
	${MPI_INCLUDE_PATH}
	src
	src/PGA
)

link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(src)
add_subdirectory(project)
