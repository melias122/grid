#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <map>
#include <string>
#include <set>
#include <functional>
#include "FitnessFunctionss.h"
#include "Statistika.h"
#include "PocetTrigramov.h"
#include "EuklidBigramy.h"
#include "EuklidTrigramy.h"
#include "ManhattanBigramy.h"
#include "ManhattanTrigramy.h"
#include "PracaSoSubormi.h"
#include "FitnessLandscape.h"


using namespace std;

Statistika* horolezec(int dlzka_hesla, string sifrovany,string plaintext, vector<FitnessFunctionss*>fitness,int pocet_inicializacii, PracaSoSubormi* subory, FitnessLandscape* landscape, int poradove_cislo) {
	vector<pair<int, int>>swapy;
	vector<int>inicialny_kluc;
	pair<vector<int>, double>vysledok;
	map<vector<int>, double>skore;
	map<vector<int>, double>zhoda;
	map<vector<int>, int>pocetnost_extremov;
	string nazov;
	Statistika *stat=new Statistika();
		
	swapy = landscape->generujSwapy(dlzka_hesla);
		
	for (vector<FitnessFunctionss*>::iterator fitit = fitness.begin(); fitit != fitness.end(); fitit++) {
		cout << "fitnes funkcia: " << (*fitit)->nazov<<endl;
			
				
		for (int k = 0; k < pocet_inicializacii; k++) {
			if ((k + 1) % (pocet_inicializacii / 50) == 0)
				cout << k << endl;
			inicialny_kluc = landscape->vygenerujKluc(dlzka_hesla);

			vysledok = landscape->landscape(sifrovany, inicialny_kluc, swapy, *fitit);

			skore.insert(vysledok);
			zhoda.insert(pair<vector<int>, double>(vysledok.first, landscape->zhodaTextov(plaintext, landscape->desifrovanie(sifrovany, vysledok.first))));

			if (pocetnost_extremov.find(vysledok.first) == pocetnost_extremov.end()) {
				pocetnost_extremov.insert(pair <vector<int>, int > (vysledok.first, 1));
			}
			else {
				(*pocetnost_extremov.find(vysledok.first)).second++;
			}
		}
		
		nazov.append("text");
		nazov.append(to_string(sifrovany.size()));
		nazov.append("_");
		nazov.append(to_string((poradove_cislo%100)));
		nazov.append("_heslo");
		nazov.append(to_string(dlzka_hesla));
		nazov.append("_");
		nazov.append((*fitit)->nazov);
		nazov.append("_");
		nazov.append("inicializacie");
		nazov.append(to_string(pocet_inicializacii));
		nazov.append(".csv");

		subory->ulozCSV(skore, zhoda, nazov,pocetnost_extremov);

		stat =new Statistika((*fitit)->nazov, sifrovany.size(), dlzka_hesla, pocet_inicializacii, skore, zhoda,pocetnost_extremov);
		nazov.clear();
		pocetnost_extremov.clear();
		skore.clear();
		zhoda.clear();
	}

	return stat;
}

void main() {
	srand(time(0));
	PracaSoSubormi* subory=new PracaSoSubormi();
	FitnessLandscape* landscape = new FitnessLandscape();

	subory->nacitajBigramy();
	subory->nacitajTrigramy();
	subory->nacitajTrigramyTop();

	vector<int>dlzky_hesiel;
	dlzky_hesiel.push_back(5);
	dlzky_hesiel.push_back(10);
	dlzky_hesiel.push_back(20);
	//dlzky_hesiel.push_back(30);
	//dlzky_hesiel.push_back(50);

	vector<int>pocet_inicializacii;
	pocet_inicializacii.push_back(1000);
	pocet_inicializacii.push_back(10000);
	//pocet_inicializacii.push_back(100000);

	vector<int>kluc;
	vector<int>inicialny_kluc;
	string sifrovany;

	EuklidBigramy *eukBi=new EuklidBigramy("euklidBigramy");
	eukBi->bigramy = subory->bigramy;
	EuklidTrigramy *eukTri=new EuklidTrigramy("euklidTrigramy");
	eukTri->trigramy = subory->trigramy;
	ManhattanBigramy *manBi=new ManhattanBigramy("manhattanBigramy");
	manBi->bigramy = subory->bigramy;
	ManhattanTrigramy *manTri=new ManhattanTrigramy("manhattanTrigramy");
	manTri->trigramy = subory->trigramy;
	PocetTrigramov *manTriTop=new PocetTrigramov("pocetTrigramov");
	manTriTop->trigramy = subory->trigramy_top;

	vector<FitnessFunctionss*> fitness;
	fitness.push_back(eukBi);
	fitness.push_back(eukTri);
	fitness.push_back(manBi);
	fitness.push_back(manTri);
	fitness.push_back(manTriTop);

	vector<pair<int, int>>swapy;
	pair<vector<int>, double>vysledok;
	map<vector<int>, double>skore;
	map<vector<int>, double>zhoda;

	string nazov1,nazov2,plaintext;
	vector<Statistika*>statistiky;
	Statistika* stat;
	ifstream subor;

	for (int i = 2201; i <= 2300; i++) {
		for (int j = 200; j <= 200; j = j + 50) {
			cout << "dlzka textu " << j << endl;
			for (int k = 0; k < dlzky_hesiel.size(); k++) {
				cout << "dlzka hesla " << dlzky_hesiel[k] << endl;
				nazov1.append("ct\\");
				nazov1.append(to_string(i));
				nazov1.append("_");
				nazov1.append(to_string(j));
				nazov1.append("_");
				nazov1.append(to_string(dlzky_hesiel[k]));
				nazov1.append(".txt");


				subor.open(nazov1);
				if (subor.is_open()) {
					subor >> sifrovany;
				}

				for (string::iterator strit = sifrovany.begin(); strit != sifrovany.end(); strit++) {
					if (*strit >= 'a' && *strit <= 'z')
						*strit = *strit - 32;
				}

				subor.close();

				nazov2.append("pt\\");
				nazov2.append(to_string(i));
				nazov2.append("_");
				nazov2.append(to_string(j));
				nazov2.append(".txt");

				subor.open(nazov2);
				if (subor.is_open()) {
					subor >> plaintext;
				}

				for (string::iterator strit = plaintext.begin(); strit != plaintext.end(); strit++) {
					if (*strit >= 'a' && *strit <= 'z')
						*strit = *strit - 32;
				}
				subor.close();

				if (sifrovany.size() > 0) {
					statistiky.push_back(horolezec(dlzky_hesiel[k], sifrovany, plaintext, fitness, 1000, subory, landscape,i));
				}

				nazov1.clear();
				nazov2.clear();
				sifrovany.clear();
				plaintext.clear();
			}
		}
	}
	//subory->statVystup(statistiky);

	cin.get();
}