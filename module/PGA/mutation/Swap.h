#ifndef mutation_Swap_h
#define mutation_Swap_h

#include "../GeneticOperation.h"

#include "utils/Random.h"

namespace Mutation
{

class Swap : public GeneticOperation::Interface
{
public:
    Swap(int swaps = 1)
        : m_swaps{ swaps }
    {
    }

    void apply(Population &population) override
    {
        int j, k;
        for (Chromosome &ch : population) {
            for (int i = 0; i < m_swaps; i++) {
                do {
                    j = Rand.Int(0, ch.size() - 1);
                    k = Rand.Int(0, ch.size() - 1);
                } while (j == k);
                std::swap(ch.genes()[j], ch.genes()[k]);
            }
        }
    }

private:
    int m_swaps;
};
}
#endif
