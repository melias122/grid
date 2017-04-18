#ifndef GENOPCROSS_H
#define GENOPCROSS_H

#include "GeneticOperation.h"

class SinglePointCrossover : public GeneticOperation
{
public:
    // numberOfChildrens must be 1 or 2
    SinglePointCrossover(int numberOfChildrens = 1)
        : m_childrens{ numberOfChildrens }
    {
    }

    void apply(Population &pop) override;

private:
    Genes crossover(const Genes &parent1, const Genes &parent2, int point);

    int m_childrens;
};

class UniformCrossover : public GeneticOperation
{
public:
    UniformCrossover(int numberOfChildrens = 1)
        : m_childrens{ numberOfChildrens }
    {
    }

    void apply(Population &pop) override;

private:
    int m_childrens;
};

#endif
