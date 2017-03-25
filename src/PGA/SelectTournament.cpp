#include "SelectTournament.h"
#include <cstdlib>

Population SelectTournament::select(Population p)
{
    Population newp;
    newp.reserve(p.size());
    for (int i = 0; i < m_subpopulationSize; i++) {
        int a = rand() % p.size();
        int b = rand() % p.size();
        Chromosome &ca = p[a];
        Chromosome &cb = p[b];
        if (ca.score() > cb.score()) {
            newp.push_back(ca);
        } else {
            newp.push_back(cb);
        }
    }
    return newp;
}
