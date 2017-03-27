#include "GA.h"
#include "GeneticOperationMutationSwap.h"
#include "Helpers.h"
#include "Migrator.h"
#include "SelectElitism.h"
#include "SelectTournament.h"

#include <iostream>

using namespace std;

GA::GA(SchemeGA *scheme, Cipher *cipher, Fitness *fitness, Migrator *migrator)
    : m_scheme{ scheme }
    , m_cipher{ cipher }
    , m_fitness{ fitness }
    , m_migrator{ migrator }
{
    static int id{ 0 };
    m_id = id++;
}

void GA::init()
{
    string plaintext;
    m_population.reserve(m_scheme->initialPopulation());
    for (int i = 0; i < m_scheme->initialPopulation(); i++) {
        Chromosome c(Helpers::rndAbcPermutation());
        m_cipher->decrypt(c.genes(), plaintext);
        double score = m_fitness->evaluate(plaintext);
        c.setScore(score);
        m_population.push_back(c);
    }
}

void GA::start()
{
    init();
    for (int i = 1; i <= m_scheme->maxIteration(); i++) {

        if (m_migrator && ((m_scheme->migrationTime() % i) == 0)) {
            Population migrated = m_migrator->migrate(m_id, m_population);
            m_population.insert(end(m_population), begin(migrated), end(migrated));
        }

        applyOperations();
    }

    string pt;
    m_cipher->decrypt(m_population[0].genes(), pt);
    cout << "GA node " << id() << " decrypted: " << pt << "\n";
}

void GA::applyOperations()
{
    string plaintext;
    Population newpop;
    newpop.reserve(m_population.size());

    for (const Operation &o : m_scheme->operations()) {

        Population selected = o.select->select(m_population);
        o.genetic->apply(selected);

        for (size_t j = 0; j < selected.size(); j++) {
            m_cipher->decrypt(selected[j].genes(), plaintext);
            double score = m_fitness->evaluate(plaintext);
            selected[j].setScore(score);
        }

        newpop.insert(newpop.begin(), selected.begin(), selected.end());
    }

    m_population = newpop;
}
