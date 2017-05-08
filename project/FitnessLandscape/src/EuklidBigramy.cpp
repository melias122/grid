#include "EuklidBigramy.h"
#include "FitnessFunctionss.h"
#include <cmath>
#include <map>
#include <vector>

EuklidBigramy::EuklidBigramy() {}

EuklidBigramy::EuklidBigramy(std::string nazov)
    : FitnessFunctionss(nazov)
{
    this->nazov = nazov;
}

EuklidBigramy::~EuklidBigramy()
{
}

void EuklidBigramy::fit()
{

    std::map<std::string, int> vyskyty;
    std::map<std::string, double>::iterator frekvencny;
    std::map<std::string, double> frekvencie;
    std::string pom;
    double vysledok = 0;

    std::vector<std::vector<int>> pocetnost(26, std::vector<int>(26, 0));

    for (int i = 0; i < this->desifrovany.size() - 1; i++) {
        pocetnost[this->desifrovany[i] - 'A'][this->desifrovany[i + 1] - 'A']++;
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            vysledok = vysledok + pow(this->bigramy[i][j] - ((double)pocetnost[i][j] / ((double)this->desifrovany.size() - 1)), 2);
        }
    }

    this->vysledok = 0 - sqrt(vysledok);
}
