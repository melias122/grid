add_executable(helloworld main.cpp)

target_link_libraries(helloworld grid)
install(TARGETS helloworld DESTINATION ${PROJECT_SOURCE_DIR}/project/helloworld)
