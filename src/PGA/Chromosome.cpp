#include "Chromosome.h"

#include "Cipher.h"
#include "Fitness.h"
#include "Random.h"

std::ostream &operator<<(std::ostream &os, const Genes &p)
{
    os << "{ ";
    for (auto &c : p) {
        os << c << " ";
    }
    return os << "}";
}

std::string to_string(const Genes &g)
{
    return std::string(g.begin(), g.end());
}

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

void append(Population &p0, const Population &p1)
{
    p0.insert(p0.end(), p1.begin(), p1.end());
}

Genes ShuffleGenerator::generate()
{
    Random.Shuffle(genes.begin(), genes.end());
    return genes;
}
