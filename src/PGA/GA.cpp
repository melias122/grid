#include "GA.h"

using std::get;
using std::shared_ptr;

Population GeneticAlgorithm::run(int id, const Scheme &scheme)
{
    Population pop, newpop;

    // create initial population
    for (int i = 0; i < scheme.initialPopulation; i++) {
        pop.emplace_back(scheme.generator.get(), scheme.cipher.get(), scheme.fitness.get());
    }

    for (int i = 1; i <= scheme.iterations; i++) {

        if (scheme.migrator) {
            scheme.migrator->migrate(id, i, pop);
        }

        newpop.clear();
        for (auto &o : scheme.operations) {

            auto &select = get<shared_ptr<Select>>(o);
            auto &geneticOperation = get<shared_ptr<GeneticOperation>>(o);

            Population selected = select->select(pop);
            geneticOperation->apply(selected);

            for (size_t j = 0; j < selected.size(); j++) {
                selected[j].calculateScore(scheme.cipher.get(), scheme.fitness.get());
            }

            newpop.insert(newpop.begin(), selected.begin(), selected.end());
        }

        pop.swap(newpop);
    }

    return pop;
}
