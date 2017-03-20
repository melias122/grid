#include "GeneticOperationMutation.h"
#include "Helpers.h"
#include <stdlib.h>     /* srand, rand */

GeneticOperationMutation::GeneticOperationMutation() {
    mutationProbability = 0.01;
}

GeneticOperationMutation::GeneticOperationMutation(float mutProb) {
    mutationProbability = mutProb;
}

GeneticOperationMutation::GeneticOperationMutation(const GeneticOperationMutation& other) {
    mutationProbability = other.mutationProbability;
}

void GeneticOperationMutation::apply(std::vector<Chromosome *>& pop) {
    // for all chromosomes
    // for all genes
    for (int i = 0; i < pop.size(); i++) {
        Chromosome *chrm = pop[i];
        for (int g = 0; g < chrm->GetLength(); g++) {
            float r = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
            if (r < mutationProbability) {
                int rnd = rand() % abcLength;
                char newChar = abcChars[rnd];
                chrm->GetGenes()->at(g) = newChar;
            }
        }
    }
}

