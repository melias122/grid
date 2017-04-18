#ifndef SEL_H
#define SEL_H

#include "Chromosome.h"

class Select
{
public:
    Select(uint subpopulationSize = 0)
        : m_subpopulationSize{ subpopulationSize }
    {
    }
    virtual Population select(Population p) { return p; }

protected:
    uint m_subpopulationSize;
};

#endif
