add_executable(gen gen.cpp)

target_link_libraries(gen
    grid
)

add_executable(pargen pargen.cpp)

target_link_libraries(pargen
	grid
)
