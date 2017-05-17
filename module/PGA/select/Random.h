#ifndef select_Random_h
#define select_Random_h

#include "Interface.h"

#include <algorithm>

namespace Select
{
class Random : public Interface
{
public:
    Random(int n)
        : n{ n }
    {
    }

    Population select(Population p)
    {
        std::random_shuffle(std::begin(p), std::end(p));
        p.resize(std::min<int>(p.size(), n));
        return p;
    }

private:
    int n;
};
}
#endif
