add_executable(pga
    src/main.cpp

    # add additional .cpp files here
)

include_directories(
	${PROJECT_SOURCE_DIR}/project/ga/src
)

target_link_libraries(pga
    libMpi
    libPGA
    libCipher
    libFitness
)
install(TARGETS pga DESTINATION ${PROJECT_SOURCE_DIR}/project/pga)
