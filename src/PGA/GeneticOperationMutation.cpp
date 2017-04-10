#include "GeneticOperationMutation.h"

#include "Random.h"

void GeneticOperationMutation::apply(Population &pop)
{
    for (Chromosome &c : pop) {
        for (auto &g : c.genes()) {
            if (Random.Double(0, 1) < m_mutationProbability) {
                g = Random.Item(m_genes);
            }
        }
    }
}
