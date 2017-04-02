#ifndef SELECT_WORST_H
#define SELECT_WORST_H

#include "Select.h"

class SelectWorst : public Select
{
public:
    SelectWorst(uint n)
        : Select(n)
    {
    }

    Population select(Population p) override;
};

#endif
