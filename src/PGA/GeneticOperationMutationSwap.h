#ifndef GENOPMUTSWAP_H
#define GENOPMUTSWAP_H

#include "GeneticOperation.h"

class GeneticOperationMutationSwap : public GeneticOperation
{
public:
    GeneticOperationMutationSwap(int swaps = 1)
        : m_swaps{ swaps }
    {
    }

    void apply(Population &population) override;

private:
    int m_swaps;
};

#endif
