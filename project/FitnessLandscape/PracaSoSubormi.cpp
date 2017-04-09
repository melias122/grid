#include "PracaSoSubormi.h"

PracaSoSubormi::PracaSoSubormi()
{
}

PracaSoSubormi::~PracaSoSubormi()
{
}

std::string PracaSoSubormi::nacitajText(std::string nazov)
{
    std::ifstream subor(nazov);
    std::string text;

    subor.open(nazov);
    if (subor.is_open()) {
        subor >> text;
    }

    for (std::string::iterator strit = text.begin(); strit != text.end(); strit++) {
        if (*strit >= 'a' && *strit <= 'z')
            *strit = *strit - 32;
    }

    return text;
}

void PracaSoSubormi::ulozCSV(std::map<std::vector<int>, double> vystup, std::map<std::vector<int>, double> zhoda, std::string nazov, std::map<std::vector<int>, int> pocetnost_extremov)
{
    std::ofstream subor(nazov);
    std::vector<int> pom;

    subor << "kluc;skore;zhoda;pocetnost" << std::endl;

    for (std::map<std::vector<int>, double>::iterator mapit = vystup.begin(); mapit != vystup.end(); mapit++) {
        pom = (*mapit).first;
        for (std::vector<int>::iterator vectit = pom.begin(); vectit != pom.end(); vectit++) {
            subor << *vectit << ",";
        }
        subor << ";" << (*mapit).second << ";" << (*zhoda.find(pom)).second << ";" << (*pocetnost_extremov.find(pom)).second << std::endl;
    }
}

void PracaSoSubormi::nacitajBigramy(const std::string &path)
{
    std::ifstream subor(path);
    std::string bigram;
    double hodnota;

    std::vector<std::vector<double>> refer(26, std::vector<double>(26, 0));

    std::map<std::string, double> bigramy;

    while (!subor.eof()) {
        subor >> bigram;
        subor >> hodnota;

        refer[bigram[0] - 'a'][bigram[1] - 'a'] = hodnota / 100.0;
    }
    this->bigramy = refer;
}

void PracaSoSubormi::nacitajTrigramy(const std::string &path)
{
    std::ifstream subor(path);
    std::string trigram;
    double hodnota;

    std::vector<std::vector<std::vector<double>>> refer(26, std::vector<std::vector<double>>(26, std::vector<double>(26, 0)));

    while (!subor.eof()) {
        subor >> trigram;
        subor >> hodnota;

        refer[trigram[0] - 'a'][trigram[1] - 'a'][trigram[2] - 'a'] = hodnota / 100.0;
    }

    this->trigramy = refer;
}

void PracaSoSubormi::nacitajTrigramyTop(const std::string &path)
{
    std::ifstream subor(path);
    std::string trigram;
    double hodnota;
    std::map<std::string, double> trigramy;

    while (!subor.eof()) {
        subor >> trigram;
        subor >> hodnota;

        trigramy.insert(std::pair<std::string, double>(trigram, hodnota));
    }

    std::map<std::string, double>::iterator trit = trigramy.end();
    trit--;

    std::vector<std::vector<std::vector<bool>>> refer(26, std::vector<std::vector<bool>>(26, std::vector<bool>(26, 0)));

    for (int i = 0; i < 1000; i++) {
        refer[(*trit).first[0] - 'a'][(*trit).first[1] - 'a'][(*trit).first[2] - 'a'] = true;
        trit--;
    }

    this->trigramy_top = refer;
}

void PracaSoSubormi::statVystup(std::vector<Statistika *> statistiky)
{
    std::ofstream subor("statistiky.csv");

    subor << "Fitness;Dlzka textu;Dlzka kluca;Pocet reinicializacii;Priemerna zhoda;Maximalna zhoda;Pocet extremov s maximalnou fitness;Skore max zhody;;Zhoda max skore;" << std::endl;

    for (std::vector<Statistika *>::iterator statit = statistiky.begin(); statit != statistiky.end(); statit++) {
        subor << (*statit)->funkcia << ";" << (*statit)->dlzka_textu << ";" << (*statit)->dlzka_kluca << ";" << (*statit)->pocet_inicializacii << ";" << (*statit)->zhoda_priemer << ";";
        subor << (*statit)->zhoda_max << ";" << (*statit)->pocet_max_fitness << ";" << (*statit)->skore_max_zhody.first << ";" << (*statit)->skore_max_zhody.second << ";" << (*statit)->zhoda_max_skore.first << ";" << (*statit)->zhoda_max_skore.second << std::endl;
    }
}
