#ifndef SCHEME_GA_H
#define SCHEME_GA_H

#include "GeneticOperation.h"
#include "Select.h"
#include <vector>

struct SelGenOp {
    Select *sel;
    GeneticOperation *op;
    SelGenOp *next{ 0 };
};

class SchemeGA
{
public:
    unsigned int migrationTime;
    unsigned int maxIteration;
    unsigned int initialPopulation;

    std::vector<SelGenOp> genOps;

    void addToSchema(SelGenOp part);

    SchemeGA(unsigned int mi, unsigned int mt, unsigned int ip);

    SchemeGA(const SchemeGA &other);
};

#endif
