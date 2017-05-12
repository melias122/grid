list(APPEND mpi_src
	    App.cpp
)

add_library(libMpi ${mpi_src})
target_link_libraries(libMpi ${Boost_LIBRARIES})
