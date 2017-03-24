#include "SelectElitism.h"
#include "Helpers.h"

Population SelectElitism::select(Population p)
{
    std::sort(std::begin(p), std::end(p), Chromosome::byBestScore());

    Population newp;
    for (int i = 0; i < GetSubPopulationSize(); i++) {
        newp.push_back(p[i]);
    }

    return newp;
}
