#ifndef crossover_SinglePoint_h
#define crossover_SinglePoint_h

#include "../GeneticOperation.h"

#include "_shared.h"

namespace Crossover
{

class SinglePoint : public GeneticOperation::Interface
{
public:
    // numberOfChildrens must be 1 or 2
    SinglePoint(int numberOfChildrens = 1)
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

        // choose random point, not begin, not end
        int point = Rand.Int(1, parent1.size() - 2);

        // erase parents
        pop.clear();

        // add childrens
        pop.emplace_back(crossover(parent1, parent2, point));
        if (m_childrens > 1) {
            pop.emplace_back(crossover(parent2, parent1, point));
        }
    }

private:
    Genes crossover(const Genes &parent1, const Genes &parent2, int point)
    {
        int genomeSize = parent1.size();

        // create empty genes of parent size
        Genes child(genomeSize, empty_gene);

        // copy parent1 genes
        for (int i = 0; i < point; i++) {
            child[i] = parent1[i];
        }

        // copy non matched parent genes
        for (int i = point; i < genomeSize; i++) {
            // if child does not have parent2 gene
            if (find(begin(child), end(child), parent2[i]) == end(child)) {
                child[i] = parent2[i];
            }
        }

        return fillEmptyGenes(child, parent1);
    }

    int m_childrens;
};
}

#endif
