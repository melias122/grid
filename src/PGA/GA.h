#ifndef GA_H
#define GA_H

#include "Scheme.h"

struct GeneticAlgorithm {
    GeneticAlgorithm() = delete;
    static Population run(int id, const Scheme &scheme);
};

#endif // GA_H
