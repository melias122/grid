#include "SelectElitism.h"

#include <algorithm>

Population SelectElitism::select(Population p)
{
    std::sort(std::begin(p), std::end(p), Chromosome::byBestScore());
    p.resize(m_subpopulationSize);
    return p;
}
