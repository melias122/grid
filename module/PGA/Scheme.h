#ifndef SCHEME_H
#define SCHEME_H

#include "Chromosome.h"
#include "GeneticOperation.h"
#include "Migrator.h"
#include "cipher/Cipher.h"
#include "fitness/Fitness.h"
#include "select/Interface.h"

#include <memory>
#include <vector>

struct Operation {
    Operation(Select::Interface *s, GeneticOperation::Interface *o)
        : select{ s }
        , geneticOperation{ o }
    {
    }

    std::shared_ptr<Select::Interface> select;
    std::shared_ptr<GeneticOperation::Interface> geneticOperation;
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

    std::vector<Operation> &addOperations(Select::Interface *s, GeneticOperation::Interface *o)
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
    LRU::Cache<Genes, double> *cache{ nullptr };

    std::vector<std::vector<Operation>> operations;
};

#endif
