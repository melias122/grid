#include "SelectRandom.h"

#include <algorithm>

Population SelectRandom::select(Population p)
{
    std::random_shuffle(std::begin(p), std::end(p));
    p.resize(m_subpopulationSize);
    return p;
}
