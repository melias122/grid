#ifndef GENOPCROSS_H
#define GENOPCROSS_H

#include "GeneticOperation.h"

class GeneticOperationCrossover : public GeneticOperation
{
    public:
        unsigned int returnCount;

        GeneticOperationCrossover();

        GeneticOperationCrossover(int retCnt);

        GeneticOperationCrossover(const GeneticOperationCrossover& other);

        void apply(std::vector<Chromosome *>& pop);
};

#endif 
