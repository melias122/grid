#ifndef FITNESS_H
#define FITNESS_H

#include "Chromosome.h"

class Fitness
{
public:
    ~Fitness() {}
    virtual double evaluate(const Genes &in) = 0;
};

#endif // FITNESS_H
