#ifndef GENOPMUTSWAPALL_H
#define GENOPMUTSWAPALL_H

#include "GeneticOperation.h"

class GeneticOperationMutationSwapAll : public GeneticOperation
{
public:
    void apply(Population &pop) override;
};

#endif
