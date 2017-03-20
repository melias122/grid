#include "GeneticOperationMutationSwapAll.h"
#include "Helpers.h"

static std::vector<std::vector<int>> comb;

GeneticOperationMutationSwapAll::GeneticOperationMutationSwapAll() {

}

void GeneticOperationMutationSwapAll::apply(std::vector<Chromosome *>& pop) {
    if (comb.empty()) {
        comb = Helpers::comb(pop[0]->GetLength(), 2);
    }
    std::vector<Chromosome *> allSwaps;
    for (int i = 0; i < pop.size(); i++) {
        for (int j = 0; j < comb.size(); j++) {
            std::vector<int> toSwap = comb[j];
            int a = toSwap[0];
            int b = toSwap[1];
            Chromosome *chrm = new Chromosome((*pop[i]));
            std::swap(chrm->GetGenes()->at(a), chrm->GetGenes()->at(b));
            allSwaps.push_back(chrm);
        }
    }
    pop.clear();
    pop.insert(pop.begin(), allSwaps.begin(), allSwaps.end());

}
