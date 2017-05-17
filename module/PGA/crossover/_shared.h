#ifndef crossover_shared_h
#define crossover_shared_h

#include <algorithm>

#define empty_gene -1

Genes fillEmptyGenes(Genes &child, Genes genome)
{
    for (auto &child_gene : child) {
        if (child_gene == empty_gene) {
            while (genome.size() > 0) {
                if (std::find(begin(child), end(child), genome.back()) == end(child)) {
                    child_gene = genome.back();
                    break;
                }
                genome.pop_back();
            }
        }
    }
    return child;
}

#endif
