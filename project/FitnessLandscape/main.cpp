#include "EuklidBigramy.h"
#include "EuklidTrigramy.h"
#include "FitnessFunctionss.h"
#include "FitnessLandscape.h"
#include "ManhattanBigramy.h"
#include "ManhattanTrigramy.h"
#include "PocetTrigramov.h"
#include "PracaSoSubormi.h"
#include "Statistika.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <time.h>
#include <vector>

#include "MpiApp.h"

using namespace std;

Statistika *horolezec(int dlzka_hesla, string sifrovany, string plaintext, vector<FitnessFunctionss *> fitness, int pocet_inicializacii, PracaSoSubormi *subory, FitnessLandscape *landscape, int poradove_cislo)
{
    vector<pair<int, int>> swapy;
    vector<int> inicialny_kluc;
    pair<vector<int>, double> vysledok;
    map<vector<int>, double> skore;
    map<vector<int>, double> zhoda;
    map<vector<int>, int> pocetnost_extremov;
    string nazov;
    Statistika *stat = new Statistika();

    swapy = landscape->generujSwapy(dlzka_hesla);

    for (vector<FitnessFunctionss *>::iterator fitit = fitness.begin(); fitit != fitness.end(); fitit++) {
        cout << "fitnes funkcia: " << (*fitit)->nazov << endl;

        for (int k = 0; k < pocet_inicializacii; k++) {
            if ((k + 1) % (pocet_inicializacii / 50) == 0)
                cout << k << endl;
            inicialny_kluc = landscape->vygenerujKluc(dlzka_hesla);

            vysledok = landscape->landscape(sifrovany, inicialny_kluc, swapy, *fitit);

            skore.insert(vysledok);
            zhoda.insert(pair<vector<int>, double>(vysledok.first, landscape->zhodaTextov(plaintext, landscape->desifrovanie(sifrovany, vysledok.first))));

            if (pocetnost_extremov.find(vysledok.first) == pocetnost_extremov.end()) {
                pocetnost_extremov.insert(pair<vector<int>, int>(vysledok.first, 1));
            } else {
                (*pocetnost_extremov.find(vysledok.first)).second++;
            }
        }

        nazov.append("text");
        nazov.append(to_string(sifrovany.size()));
        nazov.append("_");
        nazov.append(to_string((poradove_cislo % 100)));
        nazov.append("_heslo");
        nazov.append(to_string(dlzka_hesla));
        nazov.append("_");
        nazov.append((*fitit)->nazov);
        nazov.append("_");
        nazov.append("inicializacie");
        nazov.append(to_string(pocet_inicializacii));
        nazov.append(".csv");

        subory->ulozCSV(skore, zhoda, nazov, pocetnost_extremov);

        stat = new Statistika((*fitit)->nazov, sifrovany.size(), dlzka_hesla, pocet_inicializacii, skore, zhoda, pocetnost_extremov);
        nazov.clear();
        pocetnost_extremov.clear();
        skore.clear();
        zhoda.clear();
    }

    return stat;
}

// ./prog bigramy.csv trigramy.csv cesta/k/ciphertext/ cesta/k/plaintext/
int main(int argc, char **argv)
{
    MpiApp app;

    if (argc != 5) {
        cout << "Usage: " << argv[0] << " /cesta/k/bigramy.csv cesta/k/trigramy.csv /cesta/k/ciphertext/ /cesta/k/plaintext/ \n";
        return 1;
    }

    auto comm = app.communicator();
    srand(time(0));

    PracaSoSubormi *subory = new PracaSoSubormi();
    FitnessLandscape *landscape = new FitnessLandscape();

    subory->nacitajBigramy(argv[1]);
    subory->nacitajTrigramy(argv[2]);
    subory->nacitajTrigramyTop(argv[2]);

    vector<int> dlzky_hesiel;
    dlzky_hesiel.push_back(5);
    dlzky_hesiel.push_back(10);
    dlzky_hesiel.push_back(20);
    dlzky_hesiel.push_back(30);
    dlzky_hesiel.push_back(50);

    EuklidBigramy *eukBi = new EuklidBigramy("euklidBigramy");
    eukBi->bigramy = subory->bigramy;
    EuklidTrigramy *eukTri = new EuklidTrigramy("euklidTrigramy");
    eukTri->trigramy = subory->trigramy;
    ManhattanBigramy *manBi = new ManhattanBigramy("manhattanBigramy");
    manBi->bigramy = subory->bigramy;
    ManhattanTrigramy *manTri = new ManhattanTrigramy("manhattanTrigramy");
    manTri->trigramy = subory->trigramy;
    //    PocetTrigramov *manTriTop = new PocetTrigramov("pocetTrigramov");
    //    manTriTop->trigramy = subory->trigramy_top;

    vector<FitnessFunctionss *> fitness;
    fitness.push_back(eukBi);
    fitness.push_back(eukTri);
    fitness.push_back(manBi);
    fitness.push_back(manTri);
    //    fitness.push_back(manTriTop);

    vector<Statistika *> statistiky;

    // master node
    if (app.rank() == 0) {
        // posiela plaintext ciphertext pary

        for (int k = 0; k < dlzky_hesiel.size(); k++) {
            cout << "dlzka hesla " << dlzky_hesiel[k] << endl;

            for (int i = 2201; i <= 2300; i++) {
                for (int j = 200; j <= 200; j = j + 50) {
                    cout << "dlzka textu " << j << endl;

                    string path, ciphertext, plaintext;
                    path.append(argv[3]);
                    path.append(to_string(i));
                    path.append("_");
                    path.append(to_string(j));
                    path.append("_");
                    path.append(to_string(dlzky_hesiel[k]));
                    path.append(".txt");

                    ifstream subor(path);
                    if (subor.is_open()) {
                        subor >> ciphertext;
                    } else {
                        cout << "can't open " << path << "\n";
                        continue;
                    }
                    subor.close();

                    for (string::iterator strit = ciphertext.begin(); strit != ciphertext.end(); strit++) {
                        if (*strit >= 'a' && *strit <= 'z')
                            *strit = *strit - 32;
                    }

                    path.clear();
                    path.append(argv[4]);
                    path.append(to_string(i));
                    path.append("_");
                    path.append(to_string(j));
                    path.append(".txt");

                    subor.open(path);
                    if (subor.is_open()) {
                        subor >> plaintext;
                    } else {
                        cout << "can't open " << path << "\n";
                        continue;
                    }
                    subor.close();

                    for (string::iterator strit = plaintext.begin(); strit != plaintext.end(); strit++) {
                        if (*strit >= 'a' && *strit <= 'z')
                            *strit = *strit - 32;
                    }

                    if (plaintext == "" || ciphertext == "") {
                        cout << "plaintext or ciphertext empty\n";
                        continue;
                    }

                    // mpi communication

                    int workerId;

                    // wait until we have available worker
                    cout << "waiting for worker\n";
                    comm.recv<int>(mpi::any_source, 0, workerId);
                    cout << "have worker " << workerId << "\n";

                    // tell worker there is something to do
                    comm.send<int>(workerId, 0, 0);

                    comm.send<int>(workerId, 1, dlzky_hesiel[k]);
                    comm.send<string>(workerId, 2, ciphertext);
                    comm.send<string>(workerId, 3, plaintext);
                    comm.send<int>(workerId, 4, i);
                }
            }
        }

        // when everything is done, shutdown workers
        for (int i = 1; i < app.size(); i++) {
            comm.send<int>(i, 0, 1);
        }

    } else {
        // worker node
        while (1) {
            int status;

            // tell master we are free and wait for master for something to do or shutdown
            comm.sendrecv<int>(0, 0, app.rank(), 0, 0, status);

            if (status != 0) {
                // there is no more work
                break;
            }

            int dlzka_hesla, i;
            string ciphertext, plaintext;
            comm.recv<int>(0, 1, dlzka_hesla);
            comm.recv<string>(0, 2, ciphertext);
            comm.recv<string>(0, 3, plaintext);
            comm.recv<int>(0, 4, i);

            cout << "worker " << app.rank() << " running\n";
            statistiky.push_back(horolezec(dlzka_hesla, ciphertext, plaintext, fitness, 1000, subory, landscape, i));
            cout << "worker " << app.rank() << " done\n";
        }
    }
    //subory->statVystup(statistiky);

    return 0;
}
