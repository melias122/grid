#include "Chromosome.h"
#include "Helpers.h"

Chromosome::Chromosome() { m_genes = rndAbcPermutation(); }

std::string Chromosome::rndAbcPermutation()
{
    std::string perm(26, 0);
    for (int i = 0; i < perm.size(); i++) {
        perm[i] = abcChars[i];
    }
    std::random_shuffle(begin(perm), end(perm));
    return perm;
}

std::ostream& operator<<(std::ostream& os, const Chromosome& c)
{
    return os << c.m_genes;
}
