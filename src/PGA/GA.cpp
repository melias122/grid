#include "GA.h"

using std::shared_ptr;

Population GeneticAlgorithm::run(int id, const Scheme &scheme)
{
    Population pop;

    // Create initial population
    for (int i = 0; i < scheme.initialPopulation; i++) {
        pop.emplace_back(scheme.generator.get(), scheme.cipher.get(), scheme.fitness.get());
    }

    for (int i = 1; i <= scheme.iterations; i++) {

        if (scheme.migrator) {
            scheme.migrator->migrate(id, i, pop);
        }

        Population newpop;
        for (const std::vector<Operation> &ops : scheme.operations) {
            Population subpop = pop;
            for (const Operation &op : ops) {

                subpop = op.select->select(subpop);
                op.geneticOperation->apply(subpop);

                for (Chromosome &c : subpop) {
                    c.calculateScore(scheme.cipher.get(), scheme.fitness.get());
                }
            }
            append(newpop, subpop);
        }
        pop.swap(newpop);
    }

    std::sort(pop.begin(), pop.end(), Chromosome::byBestScore());

    return pop;
}
