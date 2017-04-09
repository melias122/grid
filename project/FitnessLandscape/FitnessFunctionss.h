#pragma once
#include <string>

class FitnessFunctionss
{
public:
    std::string desifrovany;
    double vysledok;
    std::string nazov;

    FitnessFunctionss();
    FitnessFunctionss(std::string nazov);
    ~FitnessFunctionss();

    virtual void fit(){};
};
