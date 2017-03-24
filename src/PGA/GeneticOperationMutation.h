#ifndef GENOPMUT_H
#define GENOPMUT_H

#include "Chromosome.h"
#include "GeneticOperation.h"

class GeneticOperationMutation : public GeneticOperation {
public:
    GeneticOperationMutation();
    GeneticOperationMutation(double mutProb);

    void apply(Population& pop) override;

private:
    double mutationProbability;
};

#endif
