#include "GeneticOperationCrossover.h"

#include "Random.h"

#define empty_gene -1

using namespace std;

void fillEmptyGenes(Genes &child, Genes genome)
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
}

void SinglePointCrossover::apply(Population &pop)
{
    if (pop.size() <= 2) {
        return;
    }

    Population newpop;
    while (newpop.size() < pop.size()) {

        // choose 2 distinct parents
        int i, j;

        do {
            i = Random.Int(0, pop.size() - 1);
            j = Random.Int(0, pop.size() - 1);
        } while (i == j);

        Genes &parent1 = pop[i].genes();
        Genes &parent2 = pop[j].genes();

        // create empty genes of parent size
        Genes child(parent1.size(), empty_gene);

        // choose random point, not begin, not end
        int point = Random.Int(1, parent1.size() - 2);

        // copy parent1 genes
        for (i = 0; i < point; i++) {
            child[i] = parent1[i];
        }

        // copy non matched parent2 genes
        for (i = point; i < parent2.size(); i++) {
            // if child does not have parent2 gene
            if (find(begin(child), end(child), parent2[i]) == end(child)) {
                child[i] = parent2[i];
            }
        }

        fillEmptyGenes(child, parent1);
        newpop.emplace_back(child);
    }

    pop.swap(newpop);
}

void UniformCrossover::apply(Population &pop)
{
    if (pop.size() <= 2) {
        return;
    }

    Population newpop;
    while (newpop.size() < pop.size()) {

        // choose 2 distinct parents
        int i, j;

        do {
            i = Random.Int(0, pop.size() - 1);
            j = Random.Int(0, pop.size() - 1);
        } while (i == j);

        Genes &parent1 = pop[i].genes();
        Genes &parent2 = pop[j].genes();

        // create empty genes of parent size
        Genes child(parent1.size(), empty_gene);

        // choose genes randomly from parent1 or parent2
        for (i = 0; i < child.size(); i++) {
            int gene;
            switch (Random.Int(0, 1)) {
            case 0:
                gene = parent1[i];
                break;
            case 1:
                gene = parent2[i];
                break;
            }

            // if child does not have gene
            if (find(begin(child), end(child), gene) == end(child)) {
                child[i] = gene;
            }
        }

        fillEmptyGenes(child, parent1);
        newpop.emplace_back(child);
    }

    pop.swap(newpop);
}
