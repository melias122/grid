#include "GeneticOperationMutationSwapAll.h"

#include "Helpers.h"

static std::vector<std::vector<int>> comb;

void GeneticOperationMutationSwapAll::apply(Population &pop)
{
    if (comb.empty()) {
        comb = Helpers::comb(pop[0].size(), 2);
    }

    Population allSwaps;
    for (int i = 0; i < pop.size(); i++) {
        for (int j = 0; j < comb.size(); j++) {
            std::vector<int> toSwap = comb[j];
            int a = toSwap[0];
            int b = toSwap[1];
            Chromosome chrm = pop[i];
            std::swap(chrm.genes()[a], chrm.genes()[b]);
            allSwaps.push_back(chrm);
        }
    }

    pop.clear();
    pop.insert(pop.begin(), allSwaps.begin(), allSwaps.end());
}
