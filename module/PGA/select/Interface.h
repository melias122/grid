#ifndef select_Interface_h
#define select_Interface_h

#include "../Chromosome.h"

namespace Select
{

class Interface
{
public:
    ~Interface() {}
    virtual Population select(Population p) { return p; }
};
}

#endif
