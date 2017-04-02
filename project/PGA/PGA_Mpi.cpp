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
    Migrator *migrator = new MpiMigrator;
    migrator->addMigration(0, 1, MigrationType::Random);
    migrator->addMigration(0, 3, MigrationType::Random);
    migrator->addMigration(1, 0, MigrationType::Best);
    migrator->addMigration(1, 3, MigrationType::Best);
    migrator->addMigration(2, 3, MigrationType::Best);

    // vytvorenie schemy genetickeho algroritmu
    SchemeGA *scheme = new SchemeGA(10000, 3000, 80);
    scheme->addOperation({ new SelectElitism(1), new GeneticOperation });
    scheme->addOperation({ new SelectElitism(1), new GeneticOperationMutationSwap(2) });
    scheme->addOperation({ new SelectTournament(15), new GeneticOperation });

    // vyber lustenej sifry
    Cipher *cipher = Monoalphabetic::fromFile(argv[1]);

    // vyber fitness funkcie
    Fitness *fitness = L1DistanceBigrams::fromFile(argv[2]);

    GA node(scheme, cipher, fitness, migrator);
    node.setId(app.rank());

    println("PGA: started");
    node.start();

    string pt;
    cipher->decrypt(node.population()[0].genes(), pt);
    println("GA node " << node.id() << " decrypted: " << pt);

    return 0;
}