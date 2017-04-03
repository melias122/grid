#include "Chromosome.h"

#include "Cipher.h"
#include "Fitness.h"
#include "Random.h"

Chromosome::Chromosome(Generator *generator, Cipher *cipher, Fitness *fitness)
{
    m_genes = generator->generate();
    calculateScore(cipher, fitness);
}

void Chromosome::calculateScore(Cipher *cipher, Fitness *fitness)
{
    std::string plaintext;
    cipher->decrypt(m_genes, plaintext);
    m_score = fitness->evaluate(plaintext);
}

std::ostream &operator<<(std::ostream &os, const Chromosome &c)
{
    return os << c.m_genes;
}

std::ostream &operator<<(std::ostream &os, const Population &p)
{
    os << "{ ";
    for (auto &c : p) {
        os << c << " ";
    }
    return os << "}";
}

Genes ShuffleGenerator::generate()
{
    Random.Shuffle(genes.begin(), genes.end());
    return genes;
}
