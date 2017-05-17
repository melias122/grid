#ifndef select_Tournament_h
#define select_Tournament_h

#include "Interface.h"

#include "utils/Random.h"

namespace Select
{
class Tournament : public Interface
{
public:
    Tournament(int n)
        : n{ n }
    {
    }

    Population select(Population p) override
    {
        Population newp;
        newp.reserve(p.size());
        for (int i = 0; i < n && i < p.size(); i++) {
            const Chromosome &ca = Rand.Item(p);
            const Chromosome &cb = Rand.Item(p);
            if (ca.score() > cb.score()) {
                newp.push_back(ca);
            } else {
                newp.push_back(cb);
            }
        }
        return newp;
    }

private:
    int n;
};
}

#endif
