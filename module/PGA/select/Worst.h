#ifndef select_Worst_h
#define select_Worst_h

#include "Interface.h"

namespace Select
{
class Worst : public Interface
{
public:
    Worst(int n)
        : n{ n }
    {
    }

    Population select(Population p)
    {
        std::sort(std::begin(p), std::end(p),
            [](const Chromosome &c1, const Chromosome &c2) {
                return c1.score() < c2.score();
            });
        p.resize(std::min<int>(p.size(), n));
        return p;
    }

private:
    int n;
};
}

#endif
