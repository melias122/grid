#ifndef SELTOUR_H
#define SELTOUR_H

#include "Select.h"

class SelectTournament : public Select
{
public:
    SelectTournament(int n)
        : Select(n)
    {
    }

    Population select(Population p);
};

#endif
