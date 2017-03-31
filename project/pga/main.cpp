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

int main(int argc, char **argv)
{
    // odstranenie argumentov 'mpirun -n 4' ./pga ...
    MpiApp app(argc, argv);

    if (app.size() != 4) {
        println("test/PGA: failed, want only 4 nodes");
        return 1;
    }

    // cesta k sifrovanemu textu a k udajom do fitness funkcie
    if (argc != 3) {
        println("usage: " << argv[0] << " ciphertext.txt fitness.csv");
        return 1;
    }

    // vytvorenie migracnej schemy
    Migrator *migrator = new MpiMigrator;
    migrator->addMigration(0, 1, Migration::Type::Random);
    migrator->addMigration(0, 3, Migration::Type::Random);
    migrator->addMigration(1, 0, Migration::Type::Best);
    migrator->addMigration(1, 3, Migration::Type::Best);
    migrator->addMigration(2, 3, Migration::Type::Best);

    // vytvorenie schemy genetickeho algroritmu
    SchemeGA *scheme = new SchemeGA(10000, 3000, 80);
    scheme->addOperation(Operation(new SelectElitism(1), new GeneticOperation));
    scheme->addOperation(Operation(new SelectElitism(1), new GeneticOperationMutationSwap(2)));
    scheme->addOperation({ new SelectTournament(15), new GeneticOperation });

    // vyber lustenej sifry
    Cipher *cipher = Monoalphabetic::fromFile(argv[1]);

    // vyber fitness funkcie
    Fitness *fitness = L1DistanceBigrams::fromFile(argv[2]);

    GA node(scheme, cipher, fitness, migrator);
    node.setId(app.rank());

    println("PGA: started");
    node.start();

    return 0;
}
