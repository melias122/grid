list(APPEND PGA_SOURCES
	GA.cpp
	Migrator.cpp
	Chromosome.cpp
)

add_library(libPGA ${PGA_SOURCES})
target_link_libraries(libPGA
    ${Boost_LIBRARIES}
)
