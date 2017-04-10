#ifndef GENOPCROSS_H
#define GENOPCROSS_H

#include "GeneticOperation.h"

class SinglePointCrossover : public GeneticOperation
{
public:
    void apply(Population &pop) override;
};

class UniformCrossover : public GeneticOperation
{
public:
    void apply(Population &pop) override;
};

#endif
