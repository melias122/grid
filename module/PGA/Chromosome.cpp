#include "Chromosome.h"

#include "cipher/Monoalphabetic.h"
#include "fitness/L1.h"
#include "utils/Random.h"

Chromosome::Chromosome(Generator *generator, Cipher *cipher, Fitness *fitness)
{
    m_genes = generator->generate();
    calculateScore(cipher, fitness);
}

void Chromosome::calculateScore(Cipher *cipher, Fitness *fitness, LRU::Cache<Genes, double> *cache)
{
    if (cache) {
        if (cache->contains(m_genes)) {
            m_score = cache->lookup(m_genes);
            return;
        }

        std::string plaintext;
        cipher->decrypt(m_genes, plaintext);
        m_score = fitness->evaluate(plaintext);

        cache->insert(m_genes, m_score);
    } else {
        std::string plaintext;
        cipher->decrypt(m_genes, plaintext);
        m_score = fitness->evaluate(plaintext);
    }
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
