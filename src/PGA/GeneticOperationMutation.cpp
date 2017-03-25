#include "GeneticOperationMutation.h"

#include "Helpers.h"

GeneticOperationMutation::GeneticOperationMutation()
{
    mutationProbability = 0.01;
}

GeneticOperationMutation::GeneticOperationMutation(double mutProb)
{
    mutationProbability = mutProb;
}

void GeneticOperationMutation::apply(Population &pop)
{
    // for all chromosomes
    // for all genes
    for (int i = 0; i < pop.size(); i++) {
        Chromosome &c = pop[i];
        for (int g = 0; g < c.size(); g++) {
            double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            if (r < mutationProbability) {
                c.genes()[g] = abcChars[rand() % sizeof(abcChars)];
            }
        }
    }
}
