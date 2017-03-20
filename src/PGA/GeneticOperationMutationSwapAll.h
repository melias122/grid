#ifndef GENOPMUTSWAPALL_H
#define GENOPMUTSWAPALL_H

#include "GeneticOperation.h"


class GeneticOperationMutationSwapAll: public GeneticOperation
{
    public:

        GeneticOperationMutationSwapAll();

        void apply(std::vector<Chromosome *>& pop);
};


#endif 
