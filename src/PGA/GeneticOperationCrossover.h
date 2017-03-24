#ifndef GENOPCROSS_H
#define GENOPCROSS_H

#include "GeneticOperation.h"

class GeneticOperationCrossover : public GeneticOperation {
public:
    void apply(Population& pop) override;

private:
    uint m_returnCount{ 1 };
};

#endif
