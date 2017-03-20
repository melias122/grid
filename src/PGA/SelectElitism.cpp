#include "SelectElitism.h"
#include "Helpers.h"

std::vector<Chromosome*> SelectElitism::select(std::vector<Chromosome*>& pop) {
    std::vector<Chromosome *> retVal;
    std::sort(pop.begin(), pop.end(),Chromosome::PointerCompare());

    for (int i = 0; i < GetSubPopulationSize(); i++) {
        retVal.push_back(new Chromosome((*pop[i])));
    }


    return retVal;
}
