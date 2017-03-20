#ifndef GENOPMUTSWAP_H
#define GENOPMUTSWAP_H

#include "GeneticOperation.h"

class GeneticOperationMutationSwap : public GeneticOperation
{
    public:
        int swapsCount;

        GeneticOperationMutationSwap();

        GeneticOperationMutationSwap(int swapCnt);

        GeneticOperationMutationSwap(const GeneticOperationMutationSwap& other);

        void apply(std::vector<Chromosome *>& pop);
};


#endif 
