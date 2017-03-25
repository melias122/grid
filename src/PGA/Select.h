#ifndef SEL_H
#define SEL_H

#include "Chromosome.h"

class Select
{
public:
    Select() {}
    Select(uint subpopulationSize)
        : m_subpopulationSize{ subpopulationSize }
    {
    }
    virtual Population select(Population p) { return p; }

protected:
    uint m_subpopulationSize{ 0 };
};

#endif
