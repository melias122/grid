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

GA *newNode(Migrator *migrator = nullptr)
{
    SchemeGA *scheme = new SchemeGA(10000, 3000, 80);
    scheme->addOperation(Operation(new SelectElitism(1), new GeneticOperation));
    scheme->addOperation(Operation(new SelectElitism(1), new GeneticOperationMutationSwap(2)));
    scheme->addOperation({ new SelectTournament(15), new GeneticOperation });

    Cipher *cipher = Monoalphabetic::fromFile("/home/melias122/code/grid/project/PGA/input/177_1000.txt");
    Fitness *fitness = L1DistanceBigrams::fromFile("/home/melias122/code/grid/project/PGA/input/fr_2.csv");

    return new GA(scheme, cipher, fitness, migrator);
}

int main(int argc, char **argv)
{
    println("test/PGA: started");

    MpiApp app;

    if (app.size() != 4) {
        println("test/PGA: failed, want only 4 nodes");
        return 1;
    }

    Migrator *migrator = new MpiMigrator;
    migrator->addMigration(0, 1, Migration::Type::Random);
    migrator->addMigration(0, 3, Migration::Type::Random);
    migrator->addMigration(1, 0, Migration::Type::Best);
    migrator->addMigration(1, 3, Migration::Type::Best);
    migrator->addMigration(2, 3, Migration::Type::Best);

    GA *gaNode = newNode(migrator);
    gaNode->setId(app.rank());
    gaNode->start();

    return 0;
}
