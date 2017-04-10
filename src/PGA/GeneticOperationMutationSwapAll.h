#ifndef GENOPMUTSWAPALL_H
#define GENOPMUTSWAPALL_H

#include "GeneticOperation.h"

class GeneticOperationMutationSwapAll : public GeneticOperation
{
public:
    GeneticOperationMutationSwapAll(int genesCount);
    void apply(Population &pop) override;

private:
    std::vector<std::vector<int>> m_comb;
};

#endif
