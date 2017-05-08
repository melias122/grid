#pragma once
#include "FitnessFunctionss.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class FitnessLandscape
{
public:
    FitnessLandscape();
    ~FitnessLandscape();

    std::pair<std::vector<int>, double> landscape(std::string sifrovany, std::vector<int> kluc, std::vector<std::pair<int, int>> swapy, FitnessFunctionss *fitness);
    double zhodaTextov(std::string prvy, std::string druhy);
    std::vector<std::pair<int, int>> generujSwapy(int velkost);
    std::vector<std::vector<int>> vyrobSusedov(std::vector<int> kluc, std::vector<std::pair<int, int>> swapy);
    std::vector<int> vygenerujKluc(int velkost);
    std::string desifrovanie(std::string cyphertext, std::vector<int> kluc);
};
