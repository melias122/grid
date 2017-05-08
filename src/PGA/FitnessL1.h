#ifndef FITNESS_L1_H
#define FITNESS_L1_H

#include "Fitness.h"

#include <lru/lru.hpp>
#include <vector>

class L1DistanceMonograms : public Fitness
{
public:
    L1DistanceMonograms(const std::vector<double> &referenceMonograms);
    static L1DistanceMonograms *fromFile(std::string path);

    double evaluate(const std::string &plaintext) override;

private:
    std::vector<double> m_monograms;
};

class L1DistanceBigrams : public Fitness
{
public:
    L1DistanceBigrams(const std::vector<std::vector<double>> &referenceBigrams);
    static L1DistanceBigrams *fromFile(std::string path);
    void setCache(LRU::Cache<std::string, double> *cache);

    double evaluate(const std::string &plaintext) override;

private:
    LRU::Cache<std::string, double> *m_cache = nullptr;
    std::vector<std::vector<double>> m_bigrams;
};

class L1DistanceTrigrams : public Fitness
{
public:
    L1DistanceTrigrams(const std::vector<std::vector<std::vector<double>>> &referenceTrigrams);
    static L1DistanceTrigrams *fromFile(std::string path);

    double evaluate(const std::string &plaintext);

private:
    std::vector<std::vector<std::vector<double>>> m_trigrams;
};

#endif // FITNESS_L1_H
