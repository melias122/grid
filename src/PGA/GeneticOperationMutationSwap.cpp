#include "GeneticOperationMutationSwap.h"

#include "Random.h"

GeneticOperationMutationSwap::GeneticOperationMutationSwap() { swapsCount = 1; }

GeneticOperationMutationSwap::GeneticOperationMutationSwap(int swapCnt)
{
    swapsCount = swapCnt;
}

void GeneticOperationMutationSwap::apply(Population &population)
{
    for (Chromosome &ch : population) {
        int i = Random.Uint64(0, ch.size() - 1);
        int j = Random.Uint64(0, ch.size() - 1);
        std::swap(ch.genes()[i], ch.genes()[j]);
    }
}
