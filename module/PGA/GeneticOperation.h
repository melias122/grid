#ifndef GENOP_H
#define GENOP_H

#include "Chromosome.h"

class GeneticOperation
{
public:
    ~GeneticOperation() {}

    virtual void apply(Population &pop) {}
};

#endif
