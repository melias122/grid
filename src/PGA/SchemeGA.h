#ifndef SCHEME_GA_H
#define SCHEME_GA_H

#include "GeneticOperation.h"
#include "Select.h"

#include <memory>
#include <vector>

using namespace std;

struct Operation {
    Operation(Select *s, GeneticOperation *o)
        : select{ s }
        , genetic{ o }
    {
    }

    shared_ptr<Select> select;
    shared_ptr<GeneticOperation> genetic;
};

class SchemeGA
{
public:
    SchemeGA(uint maxIteration, uint migrationTime, uint initialPopulation)
        : m_maxIteration{ maxIteration }
        , m_migrationTime{ migrationTime }
        , m_initialPopulation{ initialPopulation }
    {
    }

    void addOperation(const Operation &o) { m_operations.push_back(o); }
    const vector<Operation> &operations() const { return m_operations; }

    uint migrationTime() const { return m_migrationTime; }
    uint maxIteration() const { return m_maxIteration; }
    uint initialPopulation() const { return m_initialPopulation; }

private:
    vector<Operation> m_operations;

    uint m_maxIteration;
    uint m_migrationTime;
    uint m_initialPopulation;
};

#endif
