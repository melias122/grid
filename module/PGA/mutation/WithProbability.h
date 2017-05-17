#ifndef GENOPMUT_H
#define GENOPMUT_H

#include "../GeneticOperation.h"

#include "utils/Random.h"

namespace Mutation
{

class WithProbability : public GeneticOperation::Interface
{
public:
    // mutationProbability should be between <0, 1>
    WithProbability(double mutationProbability, const Genes &genes)
        : m_mutationProbability{ mutationProbability }
        , m_genes{ genes }
    {
    }

    void apply(Population &pop) override
    {
        for (Chromosome &c : pop) {
            for (auto &g : c.genes()) {
                if (Rand.Double(0, 1) < m_mutationProbability) {
                    g = Rand.Item(m_genes);
                }
            }
        }
    }

private:
    double m_mutationProbability;
    Genes m_genes;
};
}

#endif
