#include "GA.h"
#include "GeneticOperationMutationSwap.h"
#include "SelectElitism.h"
#include <iostream>
#include "Helpers.h"
#include "SelectTournament.h"
#include <iostream>
#include "Migrator.h"
#include <thread>
#include <chrono>
#include <mutex>
 
std::mutex g_display_mutex;

static int idGen = 0;

GA::GA() {
    this->id = ++idGen;
};

void GA::init(SchemeGA *sch, Cipher *c, Fitness *f) {
    this->scheme = sch;
    this->cipher = c;
    this->fitness = f;
    // init podla schemy
    for (int i = 0; i < scheme->initialPopulation; i++) {
        Chromosome *chrm = new Chromosome();
        this->population.push_back(chrm);
        std::string txt = this->cipher->decrypt((*chrm->GetGenes()));
        float score = this->fitness->evaluate(txt);
        chrm->SetScore(score);
    }
}

void GA::setMigrator(Migrator* m) {
    this->migrator = m;
}

void GA::start() {

    std::thread::id this_id = std::this_thread::get_id();

    g_display_mutex.lock();
    std::cout << "GA started on thread " << this_id << " ...\n";
    g_display_mutex.unlock();


    for (int i = 1; i <= scheme->maxIteration; i++) {
        if (i % scheme->migrationTime == 0 && this->migrator != nullptr) {
            // Helpers::printChromosome(this->population[0]);
            // std::cout << this->population[0]->GetScore() << "\n";
            std::vector<Chromosome*> newInformation;
            std::vector<Chromosome *> popCopy = Helpers::deepCopy(this->population);
            //
            this->migrator->requestMigration(this->id, popCopy, newInformation);
            //
            for (int c = 0; c < newInformation.size(); c++) {
                this->population.push_back(newInformation[c]);
            }
        }

        std::vector<Chromosome*> newPop;
        for (int c = 0; c < this->scheme->genOps.size(); c++) {
            SelGenOp sgo = this->scheme->genOps[c];
            std::vector<Chromosome*> selected = applySelGenOp(sgo, this->population);
            newPop.insert(std::end(newPop), std::begin(selected), std::end(selected));

        }

        this->population.clear();
        this->population.insert(std::end(this->population), std::begin(newPop), std::end(newPop));

    }

    std::string txt = this->cipher->decrypt((*this->population[0]->GetGenes()));
    std::cout << txt << "\n";
}

std::vector<Chromosome *> GA::applySelGenOp(SelGenOp& sgo, std::vector<Chromosome *>& subPop) {
    std::vector<Chromosome*> selected = sgo.sel->select(subPop);
    sgo.op->apply(selected);
    for (int j = 0; j < selected.size(); j++) {
        std::string txt = this->cipher->decrypt((*selected[j]->GetGenes()));
        float score = this->fitness->evaluate(txt);
        selected[j]->SetScore(score);
    }
    if (sgo.next) {
        selected = applySelGenOp((*sgo.next), selected);
    }

    return selected;
}




