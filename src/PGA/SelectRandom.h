#ifndef SELRND_H
#define SELRND_H

#include "Select.h"

class SelectRandom : public Select {
public:

    SelectRandom() : Select() {
    };

    SelectRandom(unsigned int subPopCnt) : Select(subPopCnt) {
    };

    std::vector<Chromosome *> select(std::vector<Chromosome *>& pop);
};

#endif 
