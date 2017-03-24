#include "SchemeGA.h"

void SchemeGA::addToSchema(SelGenOp part) { genOps.push_back(part); }

SchemeGA::SchemeGA(unsigned int mi, unsigned int mt, unsigned int ip)
{
    maxIteration = mi;
    migrationTime = mt;
    initialPopulation = ip;
}

SchemeGA::SchemeGA(const SchemeGA& other)
{
    migrationTime = other.migrationTime;
    maxIteration = other.maxIteration;
    initialPopulation = other.initialPopulation;
    genOps = other.genOps;
}
