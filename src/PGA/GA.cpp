#include "GA.h"
#include "GeneticOperationMutationSwap.h"
#include "Helpers.h"
#include "Migrator.h"
#include "SelectElitism.h"
#include "SelectTournament.h"
#include <chrono>
#include <iostream>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex g_display_mutex;

static int idGen = 0;

GA::GA() { id = ++idGen; }

void GA::init(SchemeGA* sch, Cipher* c, Fitness* f)
{
    cout << "GA::init" << endl;
    scheme = sch;
    cipher = c;
    fitness = f;
    // init podla schemy
    for (int i = 0; i < scheme->initialPopulation; i++) {
        Chromosome c;
        population.push_back(c);
        string txt = cipher->decrypt(c.genes());
        double score = fitness->evaluate(txt);
        c.setScore(score);
    }
}

void GA::setMigrator(Migrator* m) { migrator = m; }

void GA::start()
{

    thread::id this_id = this_thread::get_id();

    g_display_mutex.lock();
    cout << "GA started on thread " << this_id << " ...\n";
    g_display_mutex.unlock();

    for (int i = 1; i <= scheme->maxIteration; i++) {
        Population newPopulation;
        if (i % scheme->migrationTime == 0 && migrator != nullptr) {
            migrator->requestMigration(id, population, newPopulation);
            for (int j = 0; j < newPopulation.size(); j++) {
                population.push_back(newPopulation[j]);
            }
        }

        newPopulation.clear();
        for (int j = 0; j < scheme->genOps.size(); j++) {
            Population selected = applySelGenOp(scheme->genOps[j], population);
            newPopulation.insert(end(newPopulation), begin(selected), end(selected));
        }

        population = newPopulation;
    }

    string txt = cipher->decrypt(population[0].genes());
    cout << txt << "\n";
}

Population GA::applySelGenOp(SelGenOp& sgo, const Population& subPop)
{
    Population selected = sgo.sel->select(subPop);
    sgo.op->apply(selected);

    for (int j = 0; j < selected.size(); j++) {
        string txt = cipher->decrypt(selected[j].genes());
        double score = fitness->evaluate(txt);
        selected[j].setScore(score);
    }

    if (sgo.next) {
        selected = applySelGenOp((*sgo.next), selected);
    }

    return selected;
}
