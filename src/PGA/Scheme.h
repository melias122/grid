#ifndef SCHEME_H
#define SCHEME_H

#include "Chromosome.h"
#include "Cipher.h"
#include "Fitness.h"
#include "GeneticOperation.h"
#include "Migrator.h"
#include "Select.h"

#include <memory>
#include <vector>

struct Operation {
    Operation(Select *s, GeneticOperation *o)
        : select{ s }
        , geneticOperation{ o }
    {
    }

    std::shared_ptr<Select> select;
    std::shared_ptr<GeneticOperation> geneticOperation;
};

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

    std::vector<Operation> &addOperations(Select *s, GeneticOperation *o)
    {
        operations.push_back({ Operation(s, o) });
        return operations.back();
    }

    void replaceOperations(const std::vector<std::vector<Operation>> &ops)
    {
        operations = ops;
    }

    int iterations;
    int initialPopulation;

    Generator *generator;
    Cipher *cipher;
    Fitness *fitness;
    Migrator *migrator;

    std::vector<std::vector<Operation>> operations;
};

#endif
