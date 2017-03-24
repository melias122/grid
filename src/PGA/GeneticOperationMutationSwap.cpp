#include "GeneticOperationMutationSwap.h"

#include <cstdlib>

GeneticOperationMutationSwap::GeneticOperationMutationSwap() { swapsCount = 1; }

GeneticOperationMutationSwap::GeneticOperationMutationSwap(int swapCnt)
{
    swapsCount = swapCnt;
}

void GeneticOperationMutationSwap::apply(Population& population)
{
    for (Chromosome& ch : population) {
        int i = rand() % ch.size();
        int j = rand() % ch.size();
        std::swap(ch.genes()[i], ch.genes()[j]);
    }
}
