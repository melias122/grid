#include "Select.h"

Select::Select() {
    this->subPopulationSize = 1;
}

Select::Select(unsigned int subPopCnt) {
    this->subPopulationSize = subPopCnt;
}

Select::Select(const Select& other) {
    subPopulationSize = other.subPopulationSize;
}

std::vector<Chromosome *> Select::select(std::vector<Chromosome *>& pop) {
    return pop;
};


