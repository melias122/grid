#include <time.h>
#include "GeneticOperationMutationSwap.h"
#include <stdlib.h>     /* srand, rand */

GeneticOperationMutationSwap::GeneticOperationMutationSwap() {
    swapsCount = 1;
}

GeneticOperationMutationSwap::GeneticOperationMutationSwap(int swapCnt) {
    swapsCount = swapCnt;
}

GeneticOperationMutationSwap::GeneticOperationMutationSwap(const GeneticOperationMutationSwap& other) {
    swapsCount = other.swapsCount;
}

void  GeneticOperationMutationSwap::apply(std::vector<Chromosome *>& pop) {
    for (int i = 0; i < pop.size(); i++) {
        Chromosome *chrm = pop[i];
        int a = rand() % chrm->GetLength();
        int b = rand() % chrm->GetLength();
        //std::iter_swap(chrm->GetGenes().begin() + position, chrm->GetGenes().begin() + nextPosition);
        std::swap(chrm->GetGenes()->at(a), chrm->GetGenes()->at(b));
    }
    
}
