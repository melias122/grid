#pragma once
#include "FitnessFunctionss.h"
#include <vector>

class EuklidBigramy : public FitnessFunctionss
{
public:
    std::string nazov;
    std::vector<std::vector<double>> bigramy;

    EuklidBigramy(std::string nazov);

    EuklidBigramy();

    ~EuklidBigramy();

    void fit();
};
