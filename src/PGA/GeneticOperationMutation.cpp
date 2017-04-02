#include "GeneticOperationMutation.h"

#include "Helpers.h"
#include "Random.h"

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
            double r = Random.Double();
            if (r < mutationProbability) {
                c.genes()[g] = abcChars[Random.Uint64(0, sizeof(abcChars) - 1)];
            }
        }
    }
}
