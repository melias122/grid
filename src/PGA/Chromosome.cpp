#include "Chromosome.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Helpers.h"

Chromosome::Chromosome() {
    score = 0;
    length = 26;
    
    rndAbcPermutation(genes);
};

Chromosome::Chromosome(const Chromosome& other) {
    score = other.score;
    length = other.length;
    genes = other.genes;
}


void Chromosome::rndAbcPermutation(std::vector<char> &out) {
    for (int i = 0; i < 26; i++) {
        out.push_back(abcChars[i]);
    }
    std::random_shuffle(out.begin(), out.end());
}


