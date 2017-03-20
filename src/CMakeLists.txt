list(APPEND GRID_SOURCES
    app.cpp
)

add_library(grid ${GRID_SOURCES})

target_link_libraries(grid ${MPI_CXX_LIBRARIES})

add_subdirectory(PGA)
