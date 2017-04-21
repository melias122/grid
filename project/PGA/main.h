#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <unordered_map>

#include "PGA.h"

using namespace std;

#define println(msg) cout << msg << endl

// generator chromozomov
string alphabet = "abcdefghijklmnopqrstuvwxyz";

auto schemaA(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectTournament(n), new GeneticOperationMutationSwap(1));
    return x.operations;
}

auto schemaB(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectRandom(n), new GeneticOperationMutationSwap(1));
    return x.operations;
}

auto schemaC(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectTournament(n / 2), new GeneticOperationMutationSwap(1));
    x.addOperations(new SelectTournament(n / 2), new GeneticOperation);
    return x.operations;
}

auto schemaD(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectTournament(n / 2), new GeneticOperationMutationSwap(1));
    x.addOperations(new SelectRandom(n / 2), new GeneticOperation);
    return x.operations;
}

auto schemaE(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectElitism(1), new GeneticOperation);
    x.addOperations(new SelectElitism(1), new GeneticOperationMutationSwap(1));

    for (int i = 0; i < n - 2; i++) {
        x.addOperations(new SelectTournament(2), new SinglePointCrossover(2));
    }
    return x.operations;
}

auto schemaF(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectElitism(1), new GeneticOperation);
    x.addOperations(new SelectElitism(1), new GeneticOperationMutationSwap(1));

    for (int i = 0; i < n - 2; i++) {
        x.addOperations(new SelectTournament(2), new SinglePointCrossover(1));
    }
    return x.operations;
}

auto schemaG(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectElitism(1), new GeneticOperation);
    x.addOperations(new SelectElitism(1), new GeneticOperationMutationSwap(1));

    for (int i = 0; i < (n - 2) / 2; i++) {
        auto subOp = x.addOperations(new SelectTournament(2), new SinglePointCrossover(2));
        subOp.emplace_back(new Select, new GeneticOperationMutationSwap(1));
    }
    return x.operations;
}

auto schemaH(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectElitism(1), new GeneticOperation);
    x.addOperations(new SelectElitism(1), new GeneticOperationMutationSwap(1));

    for (int i = 0; i < (n - 2); i++) {
        x.addOperations(new SelectRandom(2), new SinglePointCrossover(1));
    }
    return x.operations;
}

auto schemaI(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectElitism(1), new GeneticOperation);
    x.addOperations(new SelectElitism(1), new GeneticOperationMutationSwap(1));

    for (int i = 0; i < (n - 2) / 2; i++) {
        x.addOperations(new SelectRandom(2), new SinglePointCrossover(2));
    }
    return x.operations;
}

auto schemaJ(int n)
{
    Scheme x(0, 0, 0, 0, 0);
    x.addOperations(new SelectElitism(1), new GeneticOperation);
    x.addOperations(new SelectElitism(1), new GeneticOperationMutationSwap(1));

    for (int i = 0; i < (n - 2) / 2; i++) {
        auto subOp = x.addOperations(new SelectRandom(2), new SinglePointCrossover(2));
        subOp.emplace_back(new Select, new GeneticOperationMutationSwap(1));
    }
    return x.operations;
}

using schema_func = vector<vector<Operation>>(int);
unordered_map<string, schema_func *> operationSchema = {
    { "A", &schemaA },
    { "B", &schemaB },
    { "C", &schemaC },
    { "D", &schemaD },
    { "E", &schemaE },
    { "F", &schemaF },
    { "G", &schemaG },
    { "H", &schemaH },
    { "I", &schemaI },
    { "J", &schemaJ },
};

#endif
