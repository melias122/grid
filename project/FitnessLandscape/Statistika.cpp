#include "Statistika.h"
#include <set>


Statistika::Statistika()
{
}

Statistika::~Statistika()
{
}

Statistika::Statistika(std::string funkcia, int dlzka_textu, int dlzka_kluca, int pocet_inicializacii, std::map<std::vector<int>, double> skore, std::map<std::vector<int>, double> zhoda,std::map<std::vector<int>,int>pocetnost_extremov)
{
	this->dlzka_kluca = dlzka_kluca;
	this->dlzka_textu = dlzka_textu;
	this->funkcia = funkcia;
	this->pocet_inicializacii = pocet_inicializacii;
	this->pocet_extremov = skore.size();

	double priemer = 0;
	double max_zhoda = 0;

	std::vector<int>max_zhoda_kluc;

	for (std::map<std::vector<int>, double>::iterator zhodit = zhoda.begin(); zhodit != zhoda.end(); zhodit++) {
		if ((*zhodit).second > max_zhoda) {
			max_zhoda = (*zhodit).second;
			max_zhoda_kluc = (*zhodit).first;
		}

		priemer = priemer + ((*zhodit).second * (*pocetnost_extremov.find((*zhodit).first)).second);
	}

	priemer = priemer / pocet_inicializacii;
	this->zhoda_priemer = priemer;
	this->zhoda_max = max_zhoda;

	int pocet_unikatnych_extremov = 0;
	double max_skore = -1000;
	std::vector<int>max_skore_kluc;
	std::set<double>hodnoty;

	for (std::map<std::vector<int>, double> ::iterator skorit = skore.begin(); skorit != skore.end(); skorit++) {
		if ((*skorit).second > max_skore) {
			max_skore = (*skorit).second;
			max_skore_kluc = (*skorit).first;
		}
	}

	for (std::map<std::vector<int>, double> ::iterator skorit = skore.begin(); skorit != skore.end(); skorit++) {
		if ((*skorit).second == max_skore) {
			this->pocet_max_fitness++;
		}
	}

	this->skore_max = max_skore;

	this->skore_max_zhody = std::make_pair((*skore.find(max_zhoda_kluc)).second, (*zhoda.find(max_zhoda_kluc)).second);
	this->zhoda_max_skore = std::make_pair((*zhoda.find(max_skore_kluc)).second, (*skore.find(max_skore_kluc)).second);
}
