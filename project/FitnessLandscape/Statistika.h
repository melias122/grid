#pragma once
#include <map>
#include <string>
#include <vector>

class Statistika
{
public:
    std::string funkcia;
    int dlzka_textu, dlzka_kluca, pocet_inicializacii, pocet_extremov, pocet_max_fitness = 0;
    double zhoda_priemer, zhoda_max, skore_max;
    std::pair<double, double> skore_max_zhody;
    std::pair<double, double> zhoda_max_skore;

    Statistika();
    ~Statistika();
    Statistika(std::string funkcia, int dlzka_textu, int dlzka_kluca, int pocet_inicializacii, std::map<std::vector<int>, double> skore, std::map<std::vector<int>, double> zhoda, std::map<std::vector<int>, int> pocetnost_extremov);
};
