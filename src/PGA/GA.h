#ifndef GA_H
#define GA_H

#include "Cipher.h"
#include "Fitness.h"
#include "Migrator.h"
#include "SchemeGA.h"

#include <memory>

class GA
{
public:
    GA(SchemeGA *scheme, Cipher *cipher, Fitness *fitness, Migrator *migrator = nullptr);
    void start();

    void setId(int id) { m_id = id; }
    int id() { return m_id; }
    Population &population() { return m_population; }

private:
    void init();
    void applyOperations();

    int m_id{ 0 };
    Population m_population;

    unique_ptr<SchemeGA> m_scheme;
    unique_ptr<Cipher> m_cipher;
    unique_ptr<Fitness> m_fitness;
    shared_ptr<Migrator> m_migrator;
};

#endif // GA_H
