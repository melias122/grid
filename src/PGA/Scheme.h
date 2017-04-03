#ifndef SCHEME_H
#define SCHEME_H

#include "Chromosome.h"
#include "Cipher.h"
#include "Fitness.h"
#include "GeneticOperation.h"
#include "Migrator.h"
#include "Select.h"

#include <memory>
#include <tuple>
#include <vector>

struct Scheme {
    Scheme(
        int iterations,
        int initialPopulation,
        Generator *generator,
        Cipher *cipher,
        Fitness *fitness,
        Migrator *migrator = nullptr)
        : iterations{ iterations }
        , initialPopulation{ initialPopulation }
        , generator{ generator }
        , cipher{ cipher }
        , fitness{ fitness }
        , migrator{ migrator }
    {
    }

    void addOperations(Select *s, GeneticOperation *o)
    {
        // Uses Chromosome constructor
        operations.emplace_back(std::shared_ptr<Select>(s), std::shared_ptr<GeneticOperation>(o));
    }

    int iterations;
    int initialPopulation;

    std::shared_ptr<Generator> generator;
    std::shared_ptr<Cipher> cipher;
    std::shared_ptr<Fitness> fitness;
    std::shared_ptr<Migrator> migrator;

    std::vector<std::tuple<std::shared_ptr<Select>, std::shared_ptr<GeneticOperation>>> operations;
};

#endif
