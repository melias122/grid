#pragma once
#include "Statistika.h"
#include <fstream>
#include <map>
#include <string>
#include <vector>

class PracaSoSubormi
{
public:
    std::vector<std::vector<std::vector<bool>>> trigramy_top;
    std::vector<std::vector<std::vector<double>>> trigramy;
    std::vector<std::vector<double>> bigramy;

    PracaSoSubormi();
    ~PracaSoSubormi();

    std::string nacitajText(std::string nazov);
    void ulozCSV(std::map<std::vector<int>, double> vystup, std::map<std::vector<int>, double> zhoda, std::string nazov, std::map<std::vector<int>, int> pocetnost_extremov);
    void nacitajBigramy();
    void nacitajTrigramy();
    void nacitajTrigramyTop();
    void statVystup(std::vector<Statistika *> statistiky);
};
