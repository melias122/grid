#ifndef SELRND_H
#define SELRND_H

#include "Select.h"

class SelectRandom : public Select
{
public:
    SelectRandom(uint n)
        : Select(n)
    {
    }

    Population select(Population p) override;
};

#endif
