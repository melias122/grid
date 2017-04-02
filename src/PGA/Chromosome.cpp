#include "Chromosome.h"

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
