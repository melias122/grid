#ifndef GeneticOperation_h
#define GeneticOperation_h

#include "Chromosome.h"

namespace GeneticOperation
{

// Interface for mutation and crossover operations
class Interface
{
public:
    ~Interface() {}
    virtual void apply(Population &pop) {}
};
}

#endif
