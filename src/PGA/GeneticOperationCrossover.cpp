#include "GeneticOperationCrossover.h"

GeneticOperationCrossover::GeneticOperationCrossover() {
    returnCount = 1;
}

GeneticOperationCrossover::GeneticOperationCrossover(int retCnt) {
    returnCount = retCnt;
}

GeneticOperationCrossover::GeneticOperationCrossover(const GeneticOperationCrossover& other) {
    returnCount = other.returnCount;
}

void GeneticOperationCrossover::apply(std::vector<Chromosome *>& pop) {
//   TODO permutation crossover, pridam neskor, momentalne to je nepodstatne ....

}