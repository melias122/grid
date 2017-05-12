#include "GeneticOperationCrossover.h"

#include "utils/Random.h"

#define empty_gene -1

using namespace std;

Genes fillEmptyGenes(Genes &child, Genes genome)
{
    for (auto &child_gene : child) {
        if (child_gene == empty_gene) {
            while (genome.size() > 0) {
                if (find(begin(child), end(child), genome.back()) == end(child)) {
                    child_gene = genome.back();
                    break;
                }
                genome.pop_back();
            }
        }
    }
    return child;
}

void SinglePointCrossover::apply(Population &pop)
{
    if (pop.size() != 2) {
        return;
    }

    Genes parent1 = pop[0].genes();
    Genes parent2 = pop[1].genes();

    // choose random point, not begin, not end
    int point = Random.Int(1, parent1.size() - 2);

    // erase parents
    pop.clear();

    // add childrens
    pop.emplace_back(crossover(parent1, parent2, point));
    if (m_childrens > 1) {
        pop.emplace_back(crossover(parent2, parent1, point));
    }
}

Genes SinglePointCrossover::crossover(const Genes &parent1, const Genes &parent2, int point)
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

void UniformCrossover::apply(Population &pop)
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

        if (Random.Int(0, 1)) {
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
