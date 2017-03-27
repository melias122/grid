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
#include "app.h"

#include <fstream>
#include <iostream>
#include <random>

#include <thread>
#include <time.h>

#include <boost/mpi.hpp>

using namespace std;

#define println(msg) cout << msg << endl

unique_ptr<GA> newNode(Migrator *migrator = nullptr)
{
    SchemeGA *scheme = new SchemeGA(10000, 3000, 80);
    scheme->addOperation(Operation(new SelectElitism(1), new GeneticOperation));
    scheme->addOperation(Operation(new SelectElitism(1), new GeneticOperationMutationSwap(2)));
    scheme->addOperation({ new SelectTournament(15), new GeneticOperation });

    Cipher *cipher = Monoalphabetic::fromFile("/home/melias122/code/grid/project/PGA/input/177_1000.txt");
    Fitness *fitness = L1DistanceBigrams::fromFile("/home/melias122/code/grid/project/PGA/input/fr_2.csv");

    return unique_ptr<GA>{ new GA(scheme, cipher, fitness, migrator) };
}

void testGA()
{
    while (1) {
        newNode()->start();
    }
}

void testMpiPGA_2x2(int argc = 0, char **argv = 0)
{
    println("test/PGA: started");

    boost::mpi::environment env;
    boost::mpi::communicator comm;

    srand(time(0) + comm.rank());

    if (comm.size() != 4) {
        println("test/PGA: failed, want only 4 nodes");
        return;
    }

    Migrator *migrator = new MpiMigrator(comm);
    migrator->addMigration(0, { Migration(Migration::Type::Random, 1) });
    migrator->addMigration(0, { Migration(Migration::Type::Random, 3) });
    migrator->addMigration(1, { Migration(Migration::Type::Best, 0) });
    migrator->addMigration(1, { Migration(Migration::Type::Best, 4) });
    migrator->addMigration(2, { Migration(Migration::Type::Best, 3) });

    auto gaNode = newNode(migrator);
    gaNode->setId(comm.rank());
    gaNode->start();
}

void testThreadPGA()
{
    //    migrator->addMigration();

    //    for (size_t i = 0; i < gaPool.size(); i++) {
    //        GA *ga = gaPool[i];
    //        //        ga->setMigrator(mig);
    //        if (i > 0) {
    //            GA *gaPrev = gaPool[i - 1];
    //            Migrate best = best;
    //            Migrate worst = worst;

    //            mig->buildTopology(gaPrev->getID(), best, ga->getID(), worst);
    //        }
    //    }
    //    cout << "starting gas.\n";

    //    vector<thread> tl;
    //    for (size_t i = 0; i < gaPool.size(); i++) {
    //        GA *ga = gaPool[i];
    //        tl.emplace_back(&GA::start, ga);
    //    }

    //    cout << "join.\n";

    //    for (size_t i = 0; i < tl.size(); i++) {
    //        tl[i].join();
    //    }

    //    cout << "function end.\n";
}

int main(int argc, char **argv)
{
    //    srand(time(NULL));

    //    testGA();
    testMpiPGA_2x2();

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
