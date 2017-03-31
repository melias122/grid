add_executable(PGA_Mpi PGA_Mpi.cpp)

target_link_libraries(
    PGA_Mpi

    PGA
    grid
    ${Boost_LIBRARIES}
)

add_executable(PGA_single PGA_single.cpp)

target_link_libraries(
    PGA_single

    PGA
    grid
    ${Boost_LIBRARIES}
)
