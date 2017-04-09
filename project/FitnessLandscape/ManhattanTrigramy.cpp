#include "ManhattanTrigramy.h"
#include <map>


ManhattanTrigramy::ManhattanTrigramy()
{
}


ManhattanTrigramy::~ManhattanTrigramy()
{
}

ManhattanTrigramy::ManhattanTrigramy(std::string nazov) : FitnessFunctionss(nazov) {
	this->nazov = nazov;
}

void ManhattanTrigramy::fit()
{
	std::map<std::string, int>vyskyty;
	std::map<std::string, double>::iterator frekvencny;
	std::map<std::string, double>frekvencie;
	std::string pom;
	double vysledok = 0;

	std::vector<std::vector<std::vector<int>>>pocetnost(26, std::vector<std::vector<int>>(26, std::vector<int>(26, 0)));

	for (int i = 0; i < this->desifrovany.size() - 2; i++) {
		pocetnost[this->desifrovany[i] - 'A'][this->desifrovany[i + 1] - 'A'][this->desifrovany[i + 2] - 'A']++;
	}

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			for (int k = 0; k<26; k++)
				vysledok = vysledok + abs(this->trigramy[i][j][k] - ((double)pocetnost[i][j][k] / ((double)this->desifrovany.size() - 1)));
		}
	}

	this->vysledok = 0 - vysledok;
}
