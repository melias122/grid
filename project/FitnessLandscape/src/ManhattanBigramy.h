#pragma once
#include "FitnessFunctionss.h"
#include <vector>

class ManhattanBigramy : public FitnessFunctionss
{
public:
    std::vector<std::vector<double>> bigramy;
    std::string nazov;

    ManhattanBigramy();
    ~ManhattanBigramy();
    ManhattanBigramy(std::string nazov);
    void fit();
};
