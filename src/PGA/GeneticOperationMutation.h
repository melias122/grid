#ifndef GENOPMUT_H
#define GENOPMUT_H

#include <vector>
#include "GeneticOperation.h"
#include "Chromosome.h"



class GeneticOperationMutation: public GeneticOperation
{
    public:
        float mutationProbability ;

        GeneticOperationMutation();

        GeneticOperationMutation(float mutProb);

        GeneticOperationMutation(const GeneticOperationMutation& other);

        void apply(std::vector<Chromosome *>& pop);
};

#endif 
