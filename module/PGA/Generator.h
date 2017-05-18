#ifndef Generator_h
#define Generator_h

#include "utils/Random.h"

using Genes = std::string;

class Generator
{
public:
    Generator(const std::string &alphabet)
        : genes(alphabet)
    {
    }

    virtual Genes generate() = 0;

    Genes genes;
};

class ShuffleGenerator : public Generator
{
public:
    ShuffleGenerator(const std::string &alphabet)
        : Generator{ alphabet }
    {
    }
    Genes generate() override
    {
        Rand.Shuffle(genes.begin(), genes.end());
        return genes;
    }
};

#endif
