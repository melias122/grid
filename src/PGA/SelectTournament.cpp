#include "SelectTournament.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

std::vector<Chromosome *> SelectTournament::select(std::vector<Chromosome *>& pop) {
    std::vector<Chromosome*> retVal;
    for (int i = 0; i < GetSubPopulationSize(); i++) {
        int a = rand() % pop.size();
        int b = rand() % pop.size();
        Chromosome* ca = pop[a];
        Chromosome* cb = pop[b];
        if (ca->GetScore() > cb->GetScore()) {
            retVal.push_back(new Chromosome((*ca)));
        } else {
            retVal.push_back(new Chromosome((*cb)));
        }
    }

    return retVal;
};

