#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <string>
#include <vector>

class Chromosome {
public:
    Chromosome();

    double score() const { return m_score; }

    double setScore(double score) { m_score = score; }

    int size() const { return m_genes.size(); }

    std::string& genes() { return m_genes; }

    struct byBestScore {
        inline bool operator()(const Chromosome& c1, const Chromosome& c2)
        {
            return (c1.m_score > c2.m_score);
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const Chromosome& dt);

private:
    std::string rndAbcPermutation();

    std::string m_genes;
    double m_score{ 0.0 };
};

using Population = std::vector<Chromosome>;

#endif // CHROMOSOME_H
