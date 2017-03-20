#ifndef SEL_H
#define SEL_H

#include <vector>
#include "Chromosome.h"


class Select {
public:
    Select();

    Select(unsigned int subPopCnt);

    Select(const Select& other);

    virtual std::vector<Chromosome *> select(std::vector<Chromosome *>& pop);

    void SetSubPopulationSize(unsigned int val) {
        subPopulationSize = val;
    }

    unsigned int GetSubPopulationSize() {
        return subPopulationSize;
    }



private:
    unsigned int subPopulationSize;
};

#endif 
