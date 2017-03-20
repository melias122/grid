#ifndef GENOP_H
#define GENOP_H

#include "Chromosome.h"

class GeneticOperation {
public:

    GeneticOperation();

    virtual void apply(std::vector<Chromosome *>& pop);
};

#endif 
