add_executable(helloworld main.cpp)

target_link_libraries(helloworld
	${MPI_CXX_LIBRARIES}
)
