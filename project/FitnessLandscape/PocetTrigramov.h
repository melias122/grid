#pragma once
#include "FitnessFunctionss.h"
#include <vector>

class PocetTrigramov : public FitnessFunctionss
{
public:
    std::vector<std::vector<std::vector<bool>>> trigramy;
    std::string nazov;

    PocetTrigramov();
    ~PocetTrigramov();
    PocetTrigramov(std::string nazov);
    void fit();
};