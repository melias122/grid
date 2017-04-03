list(APPEND PGA_SOURCES
	Cipher.cpp
	GA.cpp
	GeneticOperationMutationSwapAll.cpp
	SelectElitism.cpp
	GeneticOperationCrossover.cpp
	GeneticOperationMutationSwap.cpp
    Migrator.cpp
	SelectRandom.cpp
	FitnessL1.cpp
	GeneticOperationMutation.cpp
	Chromosome.cpp
	SelectTournament.cpp
	SelectWorst.cpp
)

add_library(PGA ${PGA_SOURCES})
target_link_libraries(PGA ${Boost_LIBRARIES})
