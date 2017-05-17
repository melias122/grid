#ifndef mutation_SwapAll_h
#define mutation_SwapAll_h

#include "../GeneticOperation.h"

#include "utils/Common.h"

namespace Mutation
{

class SwapAll : public GeneticOperation::Interface
{
public:
    SwapAll(int genesCount)
        : m_comb{ Helpers::comb(genesCount, 2) }
    {
    }

    void apply(Population &pop) override
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

private:
    std::vector<std::vector<int>> m_comb;
};
}

#endif
