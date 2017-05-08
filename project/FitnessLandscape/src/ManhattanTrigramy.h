#pragma once
#include "FitnessFunctionss.h"
#include <vector>

class ManhattanTrigramy : public FitnessFunctionss
{
public:
    std::vector<std::vector<std::vector<double>>> trigramy;
    std::string nazov;

    ManhattanTrigramy();
    ~ManhattanTrigramy();
    ManhattanTrigramy(std::string nazov);
    void fit();
};
