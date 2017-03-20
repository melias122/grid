#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>

class Chromosome {
public:
    Chromosome();
    Chromosome(const Chromosome& other);

    float GetScore() {
        return score;
    }

    void SetScore(float val) {
        score = val;
    }

    int GetLength() {
        return length;
    }

    void SetLength(int val) {
        length = val;
    }

    std::vector<char> * GetGenes() {
        return &genes;
    }

    void SetGenes(std::vector<char> val) {
        genes = val;
    }

    // for sort

    bool operator<(const Chromosome& other) const {
        return (score < other.score);
    }
    
     bool operator>(const Chromosome& other) const {
        return (score > other.score);
    }

    struct PointerCompare {

        bool operator()(const Chromosome* l, const Chromosome* r) {
            return *l > *r;
        }
    };


    void rndAbcPermutation(std::vector<char> &out);

protected:
    std::vector<char> genes;
    float score;
    int length;
};

#endif // CHROMOSOME_H
