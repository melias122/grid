/*
 * File:   main.cpp
 * Author: Jugin
 *
 * Created on March 2, 2017, 2:17 PM
 */

#include "Chromosome.h"
#include "Cipher.h"
#include "Fitness.h"
#include "FitnessL1.h"
#include "GA.h"
#include "GeneticOperation.h"
#include "GeneticOperationMutation.h"
#include "GeneticOperationMutationSwap.h"
#include "GeneticOperationMutationSwapAll.h"
#include "Helpers.h"
#include "SchemeGA.h"
#include "SelectElitism.h"
#include "SelectRandom.h"
#include "SelectTournament.h"
#include "SelectTournament.h"

#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <thread> /*threading*/
#include <time.h> /* time */

using namespace std;

#define println(msg) cout << msg << endl

/*
 *
 */
GA* GATest()
{
    SchemeGA* scheme = new SchemeGA(8000, 3000, 200);

    SelGenOp sg0; // pick the best one without any changes
    sg0.sel = new SelectElitism(1);
    sg0.op = new GeneticOperation(); // do nothing
    scheme->addToSchema(sg0);

    SelGenOp sg1; // pick the best one and swap
    sg1.sel = new SelectElitism(1);
    sg1.op = new GeneticOperationMutationSwap(2);
    // new GeneticOperationMutation(0.01f);
    // new GeneticOperationMutationSwapAll();
    scheme->addToSchema(sg1);

    SelGenOp sg2; // pick 18 with tournament select without any changes
    sg2.sel = new SelectTournament(15);
    sg2.op = new GeneticOperation(); // do nothing
    scheme->addToSchema(sg2);

    // EXMAPLE TO ADD ADITIONAL OPERATIONS IN CHAIN ...
    //    SelGenOp sg1Next; // pick the best one and rnd change
    //    sg1Next.sel = new SelectElitism(1);
    //    sg1Next.op = new GeneticOperationMutation(0.05); //new
    //    GeneticOperationMutationSwapAll();
    //    sg1.next = &sg1Next;

    println("GA");

    GA* ga = new GA(scheme,
        new Monoalphabetic,
        L1DistanceBigrams::fromFile("/home/melias122/code/grid/project/PGA/input/fr_2.csv"));
    ga->setCiphertextFromFile("/home/melias122/code/grid/project/PGA/input/177_1000.txt");
    return ga;
}

void PGATest(vector<GA*>& gaPool)
{
    println("PGATest started");

    Migrator* mig = new Migrator();
    println("initialising migrator.");

    for (size_t i = 0; i < gaPool.size(); i++) {
        GA* ga = gaPool[i];
        //        ga->setMigrator(mig);
        if (i > 0) {
            GA* gaPrev = gaPool[i - 1];
            Migrate best = best;
            Migrate worst = worst;

            mig->buildTopology(gaPrev->getID(), best, ga->getID(), worst);
        }
    }
    cout << "starting gas.\n";

    vector<thread> tl;
    for (size_t i = 0; i < gaPool.size(); i++) {
        GA* ga = gaPool[i];
        tl.emplace_back(&GA::start, ga);
    }

    cout << "join.\n";

    for (size_t i = 0; i < tl.size(); i++) {
        tl[i].join();
    }

    cout << "function end.\n";
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    while (1) {
        GATest()->start();
    }

    //            vector<GA*> gaPool;
    //            for (int i = 0; i < 2; i++) {
    //                GA* ga = GATest();
    //                cout << ga->getID() << " created.\n";
    //                gaPool.push_back(ga);
    //            }
    // uncomment to PGA test:
    //            PGATest(gaPool);

    // uncomment to GA test
    //	gaPool[0]->start();

    return 0;
}
