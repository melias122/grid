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
    Population applySelGenOp(SelGenOp &op, const Population &subPop);

    int getID() { return m_id; }

private:
    void init();

    int m_id{ 0 };
    Population m_population;
    string m_plaintext;

    unique_ptr<SchemeGA> m_scheme;
    unique_ptr<Cipher> m_cipher;
    unique_ptr<Fitness> m_fitness;
    unique_ptr<Migrator> m_migrator;
};

#endif // GA_H
