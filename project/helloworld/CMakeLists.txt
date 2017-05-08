add_executable(helloworld
	src/main.cpp
)

target_link_libraries(helloworld grid)
install(TARGETS helloworld DESTINATION ${PROJECT_SOURCE_DIR}/project/helloworld)
