#ifndef SELTOUR_H
#define SELTOUR_H

#include "Select.h"

class SelectTournament : public Select
{
public:
    SelectTournament()
        : Select()
    {
    }
    SelectTournament(unsigned int subPopCnt)
        : Select(subPopCnt)
    {
    }

    Population select(Population p);
};

#endif
