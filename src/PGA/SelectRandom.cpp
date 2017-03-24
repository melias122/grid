#include "SelectRandom.h"

#include <algorithm>

Population SelectRandom::select(Population p)
{
    Population newp;
    std::random_shuffle(std::begin(p), std::end(p));
    for (int i = 0; i < GetSubPopulationSize(); i++) {
        newp.push_back(p[i]);
    }
    return newp;
}
