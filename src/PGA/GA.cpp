#include "GA.h"

#include "Helpers.h"

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

    if (m_migrator) {
        m_migrator->setMigrationTime(m_scheme->migrationTime());
    }
}

void GA::init()
{
    double score;
    string plaintext, genes;
    m_population.reserve(m_scheme->initialPopulation());
    for (int i = 0; i < m_scheme->initialPopulation(); i++) {
        genes = Helpers::rndAbcPermutation();
        m_cipher->decrypt(genes, plaintext);
        score = m_fitness->evaluate(plaintext);
        m_population.emplace_back(genes, score);
    }
}

void GA::start()
{
    init();
    for (int i = 1; i <= m_scheme->maxIteration(); i++) {

        if (m_migrator) {
            m_migrator->migrate(m_id, i, m_population);
        }
        applyOperations();
    }
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
