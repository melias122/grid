#include "GeneticOperationMutationSwapAll.h"

#include "Helpers.h"

using namespace std;

GeneticOperationMutationSwapAll::GeneticOperationMutationSwapAll(int genesCount)
    : m_comb{ Helpers::comb(genesCount, 2) }
{
}

void GeneticOperationMutationSwapAll::apply(Population &pop)
{
    Population newpop;
    for (int i = 0; i < pop.size(); i++) {
        for (int j = 0; j < m_comb.size(); j++) {
            std::vector<int> toSwap = m_comb[j];
            int a = toSwap[0];
            int b = toSwap[1];
            Chromosome c = pop[i];
            std::swap(c.genes()[a], c.genes()[b]);
            newpop.push_back(c);
        }
    }
    pop.swap(newpop);
}
