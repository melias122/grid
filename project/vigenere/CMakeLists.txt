add_executable(vigenere main.cpp)

target_link_libraries(vigenere grid)
install(TARGETS vigenere DESTINATION ${PROJECT_SOURCE_DIR}/project/vigenere)
