#ifndef ELITISM_H
#define ELITISM_H

#include "Interface.h"

#include <algorithm>

namespace Select
{
class Elitism : public Interface
{
public:
    Elitism(int n)
        : n{ n }
    {
    }

    Population select(Population p) override
    {
        std::sort(std::begin(p), std::end(p), Chromosome::byBestScore());
        p.resize(std::min<int>(p.size(), n));
        return p;
    }

private:
    int n;
};
}

#endif
