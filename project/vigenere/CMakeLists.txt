add_executable(vigenere
	src/main.cpp
)

target_link_libraries(vigenere grid)
install(TARGETS vigenere DESTINATION ${PROJECT_SOURCE_DIR}/project/vigenere)
