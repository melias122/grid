#include "GeneticOperationMutationSwap.h"

#include "Random.h"

void GeneticOperationMutationSwap::apply(Population &population)
{
    int j, k;
    for (Chromosome &ch : population) {
        for (int i = 0; i < m_swaps; i++) {
            do {
                j = Random.Int(0, ch.size() - 1);
                k = Random.Int(0, ch.size() - 1);
            } while (j == k);
            std::swap(ch.genes()[j], ch.genes()[k]);
        }
    }
}
