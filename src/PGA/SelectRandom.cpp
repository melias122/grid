#include "SelectRandom.h"
#include "Helpers.h"
#include <algorithm>



std::vector<Chromosome *> SelectRandom::select(std::vector<Chromosome *>& pop) {
    std::vector<Chromosome*> retVal = Helpers::deepCopy(pop);
//    for (int i = 0; i < GetSubPopulationSize(); i++) {
//        retVal.push_back(pop[i]);
//    }
    std::random_shuffle(retVal.begin(), retVal.end());
    retVal.erase(retVal.begin()+GetSubPopulationSize(), retVal.end());
    return retVal;
};