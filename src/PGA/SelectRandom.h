#ifndef SELRND_H
#define SELRND_H

#include "Select.h"

class SelectRandom : public Select {
public:
    SelectRandom()
        : Select()
    {
    }

    SelectRandom(unsigned int subPopCnt)
        : Select(subPopCnt)
    {
    }

    Population select(Population p) override;
};

#endif
