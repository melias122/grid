#include "PocetTrigramov.h"

PocetTrigramov::PocetTrigramov() {}

PocetTrigramov::~PocetTrigramov()
{
}

PocetTrigramov::PocetTrigramov(std::string nazov)
    : FitnessFunctionss(nazov)
{
    this->nazov = nazov;
}

void PocetTrigramov::fit()
{
    int pocet = 0;

    for (int i = 0; i < this->desifrovany.size() - 2; i++) {
        if (this->trigramy[this->desifrovany[i] - 'A'][this->desifrovany[i + 1] - 'A'][this->desifrovany[i + 2] - 'A'] == true)
            pocet++;
    }
    this->vysledok = (double)pocet;
}
