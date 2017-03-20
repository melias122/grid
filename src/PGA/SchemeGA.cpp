#include "SchemeGA.h"

void SchemeGA::addToSchema(SelGenOp part) {
    this->genOps.push_back(part);
}

SchemeGA::SchemeGA(unsigned int mi, unsigned int mt, unsigned int ip) {
    this->maxIteration = mi;
    this->migrationTime = mt;
    this->initialPopulation = ip;
};

SchemeGA::SchemeGA(const SchemeGA& other) {
    this->migrationTime = other.migrationTime;
    this->maxIteration = other.maxIteration;
    this->initialPopulation = other.initialPopulation;
    this->genOps = other.genOps;
};




