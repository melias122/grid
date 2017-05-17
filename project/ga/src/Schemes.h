#ifndef SCHEMES_H
#define SCHEMES_H

#include "PGA/PGA.h"

//
// Schemy operacii
//

#include <vector>

using schema_func = std::vector<std::vector<Operation>>(int);

auto schemaA(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Tournament(n), new Mutation::Swap(1));
    return x.operations;
}

auto schemaB(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Random(n), new Mutation::Swap(1));
    return x.operations;
}

auto schemaC(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Tournament(n / 2), new Mutation::Swap(1));
    x.addOperations(new Select::Tournament(n / 2), new GeneticOperation::Interface);
    return x.operations;
}

auto schemaD(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Tournament(n / 2), new Mutation::Swap(1));
    x.addOperations(new Select::Random(n / 2), new GeneticOperation::Interface);
    return x.operations;
}

auto schemaE(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Elitism(1), new GeneticOperation::Interface);
    x.addOperations(new Select::Elitism(1), new Mutation::Swap(1));

    for (int i = 0; i < n - 2; i++) {
        x.addOperations(new Select::Tournament(2), new Crossover::SinglePoint(2));
    }
    return x.operations;
}

auto schemaF(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Elitism(1), new GeneticOperation::Interface);
    x.addOperations(new Select::Elitism(1), new Mutation::Swap(1));

    for (int i = 0; i < n - 2; i++) {
        x.addOperations(new Select::Tournament(2), new Crossover::SinglePoint(1));
    }
    return x.operations;
}

auto schemaG(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Elitism(1), new GeneticOperation::Interface);
    x.addOperations(new Select::Elitism(1), new Mutation::Swap(1));

    for (int i = 0; i < (n - 2) / 2; i++) {
        auto subOp = x.addOperations(new Select::Tournament(2), new Crossover::SinglePoint(2));
        subOp.emplace_back(new Select::Interface, new Mutation::Swap(1));
    }
    return x.operations;
}

auto schemaH(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Elitism(1), new GeneticOperation::Interface);
    x.addOperations(new Select::Elitism(1), new Mutation::Swap(1));

    for (int i = 0; i < (n - 2); i++) {
        x.addOperations(new Select::Random(2), new Crossover::SinglePoint(1));
    }
    return x.operations;
}

auto schemaI(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Elitism(1), new GeneticOperation::Interface);
    x.addOperations(new Select::Elitism(1), new Mutation::Swap(1));

    for (int i = 0; i < (n - 2) / 2; i++) {
        x.addOperations(new Select::Random(2), new Crossover::SinglePoint(2));
    }
    return x.operations;
}

auto schemaJ(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new Select::Elitism(1), new GeneticOperation::Interface);
    x.addOperations(new Select::Elitism(1), new Mutation::Swap(1));

    for (int i = 0; i < (n - 2) / 2; i++) {
        auto subOp = x.addOperations(new Select::Random(2), new Crossover::SinglePoint(2));
        subOp.emplace_back(new Select::Interface, new Mutation::Swap(1));
    }
    return x.operations;
}

#endif
