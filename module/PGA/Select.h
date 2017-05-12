#ifndef SEL_H
#define SEL_H

#include "Chromosome.h"

class Select
{
public:
    Select(int subpopulationSize = -1)
        : m_subpopulationSize{ subpopulationSize }
    {
    }
    virtual Population select(Population p) { return p; }

protected:
    int m_subpopulationSize;
};

#endif
