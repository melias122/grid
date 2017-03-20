#include "GeneticOperation.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

GeneticOperation::GeneticOperation() {
    srand(time(NULL)); // TODO: neviem presne v C++ ako sa vola konstruktor nadtriedy, teoreticky sa to da posunut hore
    std::cout << "GeneticOperation() called" << "\n";
};

void GeneticOperation::apply(std::vector<Chromosome *>& pop) {
};




