#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <string>
#include <vector>

class Chromosome
{
public:
    Chromosome(const std::string &genes = "", double score = 0)
        : m_genes{ genes }
        , m_score{ score }
    {
    }

    double score() const { return m_score; }
    void setScore(double score) { m_score = score; }
    int size() const { return m_genes.size(); }
    std::string &genes() { return m_genes; }

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

    std::string rndAbcPermutation();

    std::string m_genes;
    double m_score{ 0.0 };
};

using Population = std::vector<Chromosome>;

#endif // CHROMOSOME_H
