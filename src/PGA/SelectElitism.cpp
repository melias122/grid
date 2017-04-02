#include "SelectElitism.h"

#include <algorithm>

Population SelectElitism::select(Population p)
{
    std::sort(std::begin(p), std::end(p), Chromosome::byBestScore());
    p.resize(std::min<int>(p.size(), m_subpopulationSize));
    return p;
}
