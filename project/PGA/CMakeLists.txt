add_executable(PGA_Mpi PGA_Mpi.cpp)

target_link_libraries(
    PGA_Mpi

    PGA
    grid
)

add_executable(PGA_single PGA_single.cpp)

target_link_libraries(
    PGA_single

    PGA
    grid
)

add_executable(GA main_GA.cpp main.h)

target_link_libraries(
    GA

    PGA
    grid
)

add_executable(stat stat.cpp)
