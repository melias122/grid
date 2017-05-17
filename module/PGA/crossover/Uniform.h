#ifndef crossover_Uniform_h
#define crossover_Uniform_h

#include "../GeneticOperation.h"
#include "_shared.h"

namespace Crossover
{

class Uniform : public GeneticOperation::Interface
{
public:
    Uniform(int numberOfChildrens = 1)
        : m_childrens{ numberOfChildrens }
    {
    }

    void apply(Population &pop) override
    {
        if (pop.size() != 2) {
            return;
        }

        Genes parent1 = pop[0].genes();
        Genes parent2 = pop[1].genes();

        // create empty genes of parent size
        Genes child1(parent1.size(), empty_gene);
        Genes child2(parent1.size(), empty_gene);

        // choose genes randomly from parent1 or parent2
        for (int i = 0; i < child1.size(); i++) {
            int gene1, gene2;

            if (Rand.Int(0, 1)) {
                gene1 = parent1[i];
                gene2 = parent2[i];
            } else {
                gene1 = parent2[i];
                gene2 = parent1[i];
            }

            // if child1 does not have gene
            if (find(begin(child1), end(child1), gene1) == end(child1)) {
                child1[i] = gene1;
            }

            // if child2 does not have gene
            if (find(begin(child2), end(child2), gene2) == end(child2)) {
                child2[i] = gene2;
            }
        }

        fillEmptyGenes(child1, parent1);
        fillEmptyGenes(child2, parent1);

        // erase parents
        pop.clear();

        // add childrens
        pop.emplace_back(child1);
        if (m_childrens > 1) {
            pop.emplace_back(child2);
        }
    }

private:
    int m_childrens;
};
}
#endif
