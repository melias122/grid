#ifndef SELELIT_H
#define SELELIT_H

#include "Select.h"

class SelectElitism : public Select
{
public:
    SelectElitism(uint n)
        : Select(n)
    {
    }

    Population select(Population p) override;
};

#endif
