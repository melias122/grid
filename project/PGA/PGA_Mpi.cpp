#include <iostream>

#include "MpiApp.h"
#include "PGA.h"

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
    Migrator *migrator = new MpiMigrator(3000);
    migrator->addMigration(1, 0, Migration::Type::Best, 5);
    migrator->addMigration(2, 0, Migration::Type::Random, 15);
    migrator->addMigration(3, 0, Migration::Type::Tournament, 7);

    if (app.rank() == 0) {
        migrator->printMigrations();
    }

    // generator chromozomov
    Genes alphabet = "abcdefghijklmnopqrstuvwxyz";
    Generator *generator = new ShuffleGenerator(alphabet);

    // vyber lustenej sifry, cesta k zasifrovanemu textu sa nacita
    // ako prvy argument programu
    Cipher *cipher = Monoalphabetic::fromFile(argv[1]);

    // vyber fitness funkcie
    Fitness *fitness = L1DistanceBigrams::fromFile(argv[2]);

    // vytvorenie schemy genetickeho algroritmu
    Scheme scheme(10000, 80, generator, cipher, fitness, migrator);
    scheme.addOperations(new SelectElitism(1), new GeneticOperation);
    scheme.addOperations(new SelectElitism(1), new GeneticOperationMutationSwap(2));
    scheme.addOperations(new SelectTournament(15), new GeneticOperation);

    DBG_LOG("starting node: " << app.rank());
    Population pop = GeneticAlgorithm::run(app.rank(), scheme);

    if (app.rank() == 0) {
        string pt;
        cipher->decrypt(pop[0].genes(), pt);
        println("GA node " << app.rank() << " decrypted: " << pt);
    }

    return 0;
}
