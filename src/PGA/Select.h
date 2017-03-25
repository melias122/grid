#ifndef SEL_H
#define SEL_H

#include "Chromosome.h"

class Select
{
public:
    Select();

    Select(unsigned int subPopCnt);

    // select vracia kopiu, novu populaciu.
    virtual Population select(Population p) { return p; }

    void SetSubPopulationSize(unsigned int val) { subPopulationSize = val; }

    unsigned int GetSubPopulationSize() { return subPopulationSize; }

private:
    unsigned int subPopulationSize;
};

#endif
