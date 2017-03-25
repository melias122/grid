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
    m_id = ++id;
}

void GA::init()
{
    string txt;
    m_population.resize(m_scheme->initialPopulation);
    for (Chromosome &c : m_population) {
        m_cipher->decrypt(c.genes(), txt);
        double score = m_fitness->evaluate(txt);
        c.setScore(score);
    }
}

void GA::start()
{
    init();
    for (int i = 1; i <= m_scheme->maxIteration; i++) {
        Population newPopulation;
        if (m_migrator && ((m_scheme->migrationTime & i) == 0)) {
            m_migrator->requestMigration(m_id, m_population, newPopulation);
            m_population.insert(end(m_population), begin(newPopulation),
                end(newPopulation));
        }

        newPopulation.clear();
        for (int j = 0; j < m_scheme->genOps.size(); j++) {
            Population selected = applySelGenOp(m_scheme->genOps[j], m_population);
            newPopulation.insert(end(newPopulation), begin(selected), end(selected));
        }

        m_population = newPopulation;
    }

    m_cipher->decrypt(m_population[0].genes(), m_plaintext);
    cout << "out: " << m_plaintext << "\n";
}

Population GA::applySelGenOp(SelGenOp &sgo, const Population &subPop)
{
    Population selected = sgo.sel->select(subPop);
    sgo.op->apply(selected);

    for (size_t j = 0; j < selected.size(); j++) {
        m_cipher->decrypt(selected[j].genes(), m_plaintext);
        double score = m_fitness->evaluate(m_plaintext);
        selected[j].setScore(score);
    }

    if (sgo.next) {
        selected = applySelGenOp((*sgo.next), selected);
    }

    return selected;
}
