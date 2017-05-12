add_executable(ga
    src/main.cpp

    # add additional .cpp files here
)

target_link_libraries(ga
    libMpi
    libPGA
    libCipher
    libFitness
)
install(TARGETS ga DESTINATION ${PROJECT_SOURCE_DIR}/project/ga)
