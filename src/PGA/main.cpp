/* 
 * File:   main.cpp
 * Author: Jugin
 *
 * Created on March 2, 2017, 2:17 PM
 */

#include "Chromosome.h"
#include "GeneticOperation.h"
#include "GeneticOperationMutationSwap.h"
#include "Helpers.h"
#include "SchemeGA.h"
#include "SelectElitism.h"
#include "SelectTournament.h"
#include "GA.h"
#include "Cipher.h"
#include "Fitness.h"
#include "FitnessL1.h"
#include "GeneticOperationMutationSwapAll.h"
#include "GeneticOperationMutation.h"
#include "SelectTournament.h"
#include "SelectRandom.h"


#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <fstream>
#include <thread>       /*threading*/
#include <future>
#include <functional>

/*
 * 
 */
GA* GATest() {
    Cipher * c = new Cipher();
    c->loadCipherText("input/177_1000_num.txt");
    // std::vector<int> CipherText = c->getCipherText();
    Fitness *f = new FitnessL1(2);

    SchemeGA *scheme = new SchemeGA(10000, 1000, 50);

    SelGenOp sg0; // pick the best one without any changes
    sg0.sel = new SelectElitism(1);
    sg0.op = new GeneticOperation(); // do nothing
    scheme->addToSchema(sg0);

    SelGenOp sg1; // pick the best one and swap
    sg1.sel = new SelectElitism(1);
    sg1.op = new GeneticOperationMutationSwap(1); // new GeneticOperationMutation(0.01f); //new GeneticOperationMutationSwapAll(); 
    scheme->addToSchema(sg1);

    SelGenOp sg2; // pick 18 with tournament select without any changes
    sg2.sel = new SelectTournament(18);
    sg2.op = new GeneticOperation(); // do nothing
    scheme->addToSchema(sg2);

    // EXMAPLE TO ADD ADITIONAL OPERATIONS IN CHAIN ...
    //    SelGenOp sg1Next; // pick the best one and rnd change
    //    sg1Next.sel = new SelectElitism(1);
    //    sg1Next.op = new GeneticOperationMutation(0.05); //new GeneticOperationMutationSwapAll(); 
    //    sg1.next = &sg1Next;


    GA *ga = new GA();
    ga->init(scheme, c, f);
    return ga;
}

void PGATest(std::vector<GA*>& gaPool) {
    std::cout << "PGATest started.\n";

    Migrator *mig = new Migrator();
    std::cout << "initialising migrator.\n";

    for (int i = 0; i < gaPool.size(); i++) {
        GA *ga = gaPool[i];
        ga->setMigrator(mig);
        if (i > 0) {
            GA *gaPrev = gaPool[i - 1];
            Migrate best = best;
            Migrate worst = worst;

            mig->buildTopology(gaPrev->getID(), best, ga->getID(), worst);
        }
    }
    std::cout << "starting gas.\n";

    std::vector<std::thread> tl;
    for (int i = 0; i < gaPool.size(); i++) {
        GA *ga = gaPool[i];
        tl.emplace_back(&GA::start, ga);
    }

    std::cout << "join.\n";

    for (int i = 0; i < tl.size(); i++) {
        tl[i].join();
    }

    std::cout << "function end.\n";

}

void mutationTest() {
    Chromosome *c = new Chromosome();
    Helpers::printChromosome(c);

    std::vector<Chromosome*> pop;
    pop.push_back(c);
    float mutationProbability = 0.05;
    for (int i = 0; i < pop.size(); i++) {
        Chromosome *chrm = pop[i];
        for (int g = 0; g < chrm->GetLength(); g++) {
            float r = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
            std::cout << "prob: " << r << "\n";
            if (r < mutationProbability) {
                std::cout << "less than: " << mutationProbability << "\n";
                int rnd = rand() % abcLength;
                std::cout << "index: " << g << "\n";

                char newChar = abcChars[rnd];
                std::cout << "to: : " << newChar << "\n";

                chrm->GetGenes()->at(g) = newChar;
                Helpers::printChromosome(chrm);

            }
        }
    }
}

void swapAllTest() {
    Chromosome *c = new Chromosome();
    Helpers::printChromosome(c);

    std::vector<Chromosome*> pop;
    pop.push_back(c);
    std::vector<std::vector<int>> comb = Helpers::comb(pop[0]->GetLength(), 2);
  
    std::vector<Chromosome *> allSwaps;
    for (int p = 0; p < pop.size(); p++) {
        for (int i = 0; i < comb.size(); i++) {
            std::vector<int> toSwap = comb[i];
            std::cout << toSwap[0] << "," << toSwap[1] << "\n";
            int a = toSwap[0];
            int b = toSwap[1];
            Helpers::printChromosome(pop[p]);
            Chromosome *chrm = new Chromosome((*pop[p]));
            std::cout << "before:\n";
            Helpers::printChromosome(chrm);
            std::swap(chrm->GetGenes()->at(a), chrm->GetGenes()->at(b));
            std::cout << "after:\n";
            Helpers::printChromosome(chrm);
            allSwaps.push_back(chrm);
        }
    }
    for (int i = 0; i < pop.size(); i++) {
        Helpers::printChromosome(pop.at(i));
    }
}

void sortTest() {
    Cipher * cipher = new Cipher();
    cipher->loadCipherText("input/177_1000_num.txt");
    Fitness *fitness = new FitnessL1(2);

    std::vector<Chromosome*> v;
    for (int i = 0; i < 15; i++) {
        Chromosome *c = new Chromosome();
        v.push_back(c);
        //
        std::string txt = cipher->decrypt((*c->GetGenes()));
        float score = fitness->evaluate(txt);
        c->SetScore(score);
    }

    for (int i = 0; i < 15; i++) {
        std::cout << i << v[i]->GetScore() << "\n";
    }


    std::sort(v.begin(), v.end(), Chromosome::PointerCompare());
    std::cout << "sorted:\n";

    for (int i = 0; i < 15; i++) {
        std::cout << i << v[i]->GetScore() << "\n";
    }
}

void vectorTest() {
    Chromosome *c = new Chromosome();
    Chromosome *c2 = new Chromosome();
    Chromosome *c3 = new Chromosome();
    Helpers::printChromosome(c);
    Helpers::printChromosome(c2);
    Helpers::printChromosome(c3);


    std::vector<Chromosome*> chv;
    chv.push_back(c);
    GeneticOperationMutationSwap *gs = new GeneticOperationMutationSwap();
    //chv = *(gs->apply(&chv));
    gs->apply(chv);
    Helpers::printChromosome(chv.at(0));

    std::vector<char> tmp;
    for (int i = 0; i < 26; i++) {
        tmp.push_back(i + 'a');
    }
    std::random_shuffle(tmp.begin(), tmp.end());
    for (int i = 0; i < 26; i++) {
        std::cout << tmp[i] << " ";
    }
    std::cout << "\n";
    std::swap(tmp[0], tmp[1]);
    for (int i = 0; i < 26; i++) {
        std::cout << tmp[i] << " ";
    }
    std::cout << "\n";

    int a = 0; //rand() % c->GetLength();
    int b = 1; //rand() % c->GetLength();
    std::cout << a << "\n";
    std::cout << b << "\n";

    std::vector<char> *ex = c->GetGenes();
    std::swap(ex->at(a), ex->at(b));
    //std::iter_swap(ex.begin() + position, ex.begin() + nextPosition);

    Helpers::printChromosome(c);
}

int main(int argc, char** argv) {

    std::vector<GA *> gaPool;
    for (int i = 0; i < 10; i++) {
        GA * ga = GATest();
        std::cout << ga->getID() << " created.\n";
        gaPool.push_back(ga);
    }
    // uncomment to PGA test:
//    PGATest(gaPool);
    
    // uncomment to GA test
    gaPool[0]->start();

    return 0;
}
