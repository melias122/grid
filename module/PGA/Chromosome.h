#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <lru/cache.hpp>
#include <string>
#include <vector>

#include "Generator.h"
#include "cipher/Cipher.h"
#include "fitness/Fitness.h"

class Cipher;
class Fitness;

class Chromosome
{
public:
    Chromosome(const Genes &genes = Genes(), double score = .0)
        : m_genes{ genes }
        , m_score{ score }
    {
    }

    Chromosome(Generator *generator, Cipher *cipher, Fitness *fitness);

    double score() const { return m_score; }
    void calculateScore(Cipher *cipher, Fitness *fitness, LRU::Cache<Genes, double> *cache = nullptr);
    int size() const { return m_genes.size(); }
    Genes &genes() { return m_genes; }

    struct byBestScore {
        inline bool operator()(const Chromosome &c1, const Chromosome &c2) const
        {
            return c1.score() > c2.score();
        }
    };

    friend std::ostream &operator<<(std::ostream &os, const Chromosome &dt);

private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &m_genes;
        ar &m_score;
    }

    Genes m_genes;
    double m_score;
};

using Population = std::vector<Chromosome>;
std::ostream &operator<<(std::ostream &os, const Population &p);
void append(Population &p0, const Population &p1);

#endif // CHROMOSOME_H
