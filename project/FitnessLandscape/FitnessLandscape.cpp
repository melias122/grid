#include "FitnessLandscape.h"

FitnessLandscape::FitnessLandscape()
{
}

FitnessLandscape::~FitnessLandscape()
{
}

std::pair<std::vector<int>, double> FitnessLandscape::landscape(std::string sifrovany, std::vector<int> kluc, std::vector<std::pair<int, int>> swapy, FitnessFunctionss *fitness)
{
    bool najdene = true;
    std::string desifrovany;
    fitness->desifrovany = desifrovanie(sifrovany, kluc);
    fitness->fit();
    double naj = fitness->vysledok;
    double skore;
    std::vector<int> best = kluc;
    std::vector<std::vector<int>> susedia;
    std::vector<int> akt;
    std::multimap<double, std::vector<int>> hodnotenie;
    std::multimap<double, std::vector<int>>::iterator hodit;

    while (najdene == true) {
        hodnotenie.clear();
        susedia = vyrobSusedov(best, swapy);

        for (std::vector<std::vector<int>>::iterator susedit = susedia.begin(); susedit != susedia.end(); susedit++) {
            fitness->desifrovany = desifrovanie(sifrovany, *susedit);
            fitness->fit();
            hodnotenie.insert(std::pair<double, std::vector<int>>(fitness->vysledok, *susedit));
            fitness->vysledok = 0;
        }

        hodit = hodnotenie.end();
        hodit--;

        if (naj < (*hodit).first) {
            naj = (*hodit).first;
            best = (*hodit).second;
            najdene = true;
        } else
            najdene = false;
    }

    return std::make_pair(best, naj);
}

double FitnessLandscape::zhodaTextov(std::string prvy, std::string druhy)
{
    std::string::iterator druhit = druhy.begin();
    int pocet = 0;

    for (std::string::iterator prvit = prvy.begin(); prvit != prvy.end(); prvit++) {
        if (*prvit == *druhit)
            pocet++;
        druhit++;
    }
    return (double)pocet / (double)prvy.size();
}

std::vector<std::pair<int, int>> FitnessLandscape::generujSwapy(int velkost)
{
    std::vector<std::pair<int, int>> swapy;
    for (int i = 0; i < velkost - 1; i++) {
        for (int j = i + 1; j < velkost; j++) {
            swapy.push_back(std::make_pair(i, j));
        }
    }
    return swapy;
}

std::vector<std::vector<int>> FitnessLandscape::vyrobSusedov(std::vector<int> kluc, std::vector<std::pair<int, int>> swapy)
{
    std::vector<std::vector<int>> vrat;
    int pom;
    std::vector<int> pomkluc;

    for (std::vector<std::pair<int, int>>::iterator swapit = swapy.begin(); swapit != swapy.end(); swapit++) {
        pomkluc = kluc;
        pom = pomkluc[(*swapit).first];
        pomkluc[(*swapit).first] = pomkluc[(*swapit).second];
        pomkluc[(*swapit).second] = pom;
        vrat.push_back(pomkluc);
    }

    return vrat;
}

std::vector<int> FitnessLandscape::vygenerujKluc(int velkost)
{
    int cislo;
    std::vector<int> kluc;
    std::set<int> cisla;

    while (kluc.size() < velkost) {
        cislo = rand() % velkost + 1;
        if (cisla.find(cislo) == cisla.end()) {
            kluc.push_back(cislo);
            cisla.insert(cislo);
        }
    }
    return kluc;
}

std::string FitnessLandscape::desifrovanie(std::string cyphertext, std::vector<int> kluc)
{
    std::string desifrovany_plaintext;

    std::string pom;
    int i = 0;

    while (desifrovany_plaintext.size() < cyphertext.size()) {
        pom = cyphertext.substr(i, kluc.size());
        for (std::vector<int>::iterator klucit = kluc.begin(); klucit != kluc.end(); klucit++) {
            desifrovany_plaintext.push_back(pom.at(*klucit - 1));
        }
        i = i + kluc.size();
    }
    return desifrovany_plaintext;
}
