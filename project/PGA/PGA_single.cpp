#include <iostream>

#include "PGA.h"

using namespace std;

#define println(msg) cout << msg << endl

int main(int argc, char **argv)
{
    // cesta k sifrovanemu textu a k udajom do fitness funkcie
    if (argc != 3) {
        println("usage: " << argv[0] << " ciphertext.txt fitness.csv");
        return 1;
    }

    // generator pociatocnej populacie
    Genes alphabet = "abcdefghijklmnopqrstuvwxyz";
    Generator *generator = new ShuffleGenerator(alphabet);

    // vyber lustenej sifry
    Cipher *cipher = Monoalphabetic::fromFile(argv[1]);
    // Cipher *cipher = Monoalphabetic::fromFile("/home/melias122/code/grid/project/PGA/input/177_1000.txt");

    // vyber fitness funkcie
    Fitness *fitness = L1DistanceBigrams::fromFile(argv[2]);
    // Fitness *fitness = L1DistanceBigrams::fromFile("/home/melias122/code/grid/project/PGA/input/fr_2.csv");

    // vytvorenie schemy genetickeho algroritmu
    Scheme scheme(10000, 80, generator, cipher, fitness);
    scheme.addOperations(new SelectElitism(1), new GeneticOperation);
    scheme.addOperations(new SelectElitism(1), new GeneticOperationMutationSwap(2));
    scheme.addOperations(new SelectTournament(15), new GeneticOperation);

    println("GeneticAlgorithm started");
    Population pop = GeneticAlgorithm::run(0, scheme);

    string pt;
    cipher->decrypt(pop[0].genes(), pt);
    println("GeneticAlgorithm decrypted = " << pt);

    return 0;
}
