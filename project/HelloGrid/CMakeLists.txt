add_executable(HelloGrid
    src/main.cpp

    # add more .cpp files here
    # src/file.cpp
)

target_link_libraries(HelloGrid 
    libMpi
    
    # add more libs here
    # libPGA, libCipher, libFitness, ...
)
install(TARGETS HelloGrid DESTINATION ${PROJECT_SOURCE_DIR}/project/HelloGrid)
