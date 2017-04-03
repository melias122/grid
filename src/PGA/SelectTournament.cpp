#include "SelectTournament.h"

#include "Random.h"

Population SelectTournament::select(Population p)
{
    Population newp;
    newp.reserve(p.size());
    for (int i = 0; i < m_subpopulationSize && i < p.size(); i++) {
        Chromosome &ca = p[Random.Uint64(0, p.size() - 1)];
        Chromosome &cb = p[Random.Uint64(0, p.size() - 1)];
        if (ca.score() > cb.score()) {
            newp.push_back(ca);
        } else {
            newp.push_back(cb);
        }
    }
    return newp;
}
