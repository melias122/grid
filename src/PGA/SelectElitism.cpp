#include "SelectElitism.h"
#include "Helpers.h"

Population SelectElitism::select(Population p)
{
    std::sort(std::begin(p), std::end(p), Chromosome::byBestScore());
    p.resize(m_subpopulationSize);
    return p;
}
