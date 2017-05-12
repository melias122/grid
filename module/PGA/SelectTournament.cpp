#include "SelectTournament.h"

#include "utils/Random.h"

Population SelectTournament::select(Population p)
{
    Population newp;
    newp.reserve(p.size());
    for (int i = 0; i < m_subpopulationSize && i < p.size(); i++) {
        const Chromosome &ca = Random.Item(p);
        const Chromosome &cb = Random.Item(p);
        if (ca.score() > cb.score()) {
            newp.push_back(ca);
        } else {
            newp.push_back(cb);
        }
    }
    return newp;
}
