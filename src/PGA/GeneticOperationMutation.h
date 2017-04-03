#ifndef GENOPMUT_H
#define GENOPMUT_H

#include "GeneticOperation.h"

class GeneticOperationMutation : public GeneticOperation
{
public:
    // mutationProbability should be between <0, 1>
    GeneticOperationMutation(double mutationProbability, const Genes &genes)
        : m_mutationProbability{ mutationProbability }
        , m_genes{ genes }
    {
    }
    void apply(Population &pop) override;

private:
    double m_mutationProbability;
    Genes m_genes;
};

#endif
