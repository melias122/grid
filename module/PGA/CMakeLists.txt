list(APPEND PGA_SOURCES
	GA.cpp
	GeneticOperationMutationSwapAll.cpp
	SelectElitism.cpp
	GeneticOperationCrossover.cpp
	GeneticOperationMutationSwap.cpp
    Migrator.cpp
	SelectRandom.cpp
	GeneticOperationMutation.cpp
	Chromosome.cpp
	SelectTournament.cpp
	SelectWorst.cpp
)

add_library(libPGA ${PGA_SOURCES})
target_link_libraries(libPGA
    ${Boost_LIBRARIES}
)
