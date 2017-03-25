#ifndef SELELIT_H
#define SELELIT_H

#include "Select.h"

class SelectElitism : public Select
{
public:
    SelectElitism()
        : Select()
    {
    }

    SelectElitism(unsigned int subPopCnt)
        : Select(subPopCnt)
    {
    }

    Population select(Population p) override;
};

#endif
