#ifndef GENOPMUTSWAP_H
#define GENOPMUTSWAP_H

#include "GeneticOperation.h"

class GeneticOperationMutationSwap : public GeneticOperation {
public:
    GeneticOperationMutationSwap();
    GeneticOperationMutationSwap(int swapCnt);

    void apply(Population& population) override;

private:
    int swapsCount;
};

#endif
