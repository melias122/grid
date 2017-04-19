#include "main.h"

vector<vector<Operation>> op1 = {
    {
        { new SelectTournament(60), new GeneticOperationMutationSwap },
        { new SelectRandom(30), new SinglePointCrossover },
        { new SelectElitism(30), new GeneticOperation },
    },

    {
        { new SelectRandom(40), new UniformCrossover },
        { new SelectElitism(20), new GeneticOperation },
    },

    {
        { new SelectTournament(10), new GeneticOperation },
    },

    {
        { new SelectRandom(5), new GeneticOperationMutationSwap },
    }
};

int main(int argc, char **argv)
{
    string ct("../project/PGA/input/177_1000.txt");
    string fr("../project/PGA/input/fr_3.csv");

    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    // generator pociatocnej populacie
    Generator *generator = new ShuffleGenerator(alphabet);

    // vyber lustenej sifry
    Cipher *cipher = Monoalphabetic::fromFile(ct);

    // vyber fitness funkcie
    Fitness *fitness = L1DistanceTrigrams::fromFile(fr);

    // vytvorenie schemy genetickeho algroritmu
    Scheme scheme(1550, 80, generator, cipher, fitness);
    scheme.replaceOperations(op1);

    println("GeneticAlgorithm started");
    Population pop = GeneticAlgorithm::run(0, scheme);

    string pt;
    cipher->decrypt(pop[0].genes(), pt);
    println("GeneticAlgorithm decrypted = " << pt);

    return 0;
}
