add_executable(pga main.cpp)

target_link_libraries(pga
    PGA
    grid
    ${Boost_LIBRARIES}
)
