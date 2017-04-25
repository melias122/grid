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

enum {
    tag_status,
    tag_dlzka_hesla,
    tag_ciphertext,
    tag_plaintext,
    tag_poradove_cislo,
    tag_worker,

    status_work,
    status_exit
};

void horolezec(int dlzka_hesla, string sifrovany, string plaintext, vector<FitnessFunctionss *> fitness, int pocet_inicializacii, PracaSoSubormi *subory, FitnessLandscape *landscape, int poradove_cislo)
{
    vector<pair<int, int>> swapy;
    vector<int> inicialny_kluc;
    pair<vector<int>, double> vysledok;
    map<vector<int>, double> skore;
    map<vector<int>, double> zhoda;
    map<vector<int>, int> pocetnost_extremov;
    string nazov;

    swapy = landscape->generujSwapy(dlzka_hesla);

    for (vector<FitnessFunctionss *>::iterator fitit = fitness.begin(); fitit != fitness.end(); fitit++) {
        for (int k = 0; k < pocet_inicializacii; k++) {
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

        nazov.clear();
        pocetnost_extremov.clear();
        skore.clear();
        zhoda.clear();
    }
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

    PracaSoSubormi subory;
    FitnessLandscape landscape;

    subory.nacitajBigramy(argv[1]);
    subory.nacitajTrigramy(argv[2]);
    subory.nacitajTrigramyTop(argv[2]);

    vector<int> dlzky_hesiel;
    dlzky_hesiel.push_back(5);
    dlzky_hesiel.push_back(10);
    dlzky_hesiel.push_back(20);
    //    dlzky_hesiel.push_back(30);
    //    dlzky_hesiel.push_back(50);

    EuklidBigramy eukBi("euklidBigramy");
    eukBi.bigramy = subory.bigramy;
    EuklidTrigramy eukTri("euklidTrigramy");
    eukTri.trigramy = subory.trigramy;
    ManhattanBigramy manBi("manhattanBigramy");
    manBi.bigramy = subory.bigramy;
    ManhattanTrigramy manTri("manhattanTrigramy");
    manTri.trigramy = subory.trigramy;
    PocetTrigramov manTriTop("pocetTrigramov");
    manTriTop.trigramy = subory.trigramy_top;

    vector<FitnessFunctionss *> fitness;
    //    fitness.push_back(&eukBi);
    //    fitness.push_back(&eukTri);
    fitness.push_back(&manBi);
    fitness.push_back(&manTri);
    //    fitness.push_back(&manTriTop);

    if (app.rank() == 0) {
        // master node

        for (int k = 0; k < dlzky_hesiel.size(); k++) {
            for (int i = 1; i <= 4000; i++) {
                for (int j = 50; j <= 2000; j = j + 50) {

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
                        cout << "M:can't open " << path << "\n";
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
                        cout << "M:can't open " << path << "\n";
                        continue;
                    }
                    subor.close();

                    for (string::iterator strit = plaintext.begin(); strit != plaintext.end(); strit++) {
                        if (*strit >= 'a' && *strit <= 'z')
                            *strit = *strit - 32;
                    }

                    if (plaintext == "" || ciphertext == "") {
                        cout << "M:plaintext or ciphertext empty\n";
                        continue;
                    }

                    // mpi communication

                    int worker;

                    // wait until we have available worker
                    cout << "M:waiting for worker" << endl;
                    comm.recv<int>(mpi::any_source, tag_worker, worker);
                    cout << "M:sending work (dlzka_hesla=" << dlzky_hesiel[k] << ",poradove_cislo=" << i << ",dlzka_textu=" << j << ") to " << worker << endl;

                    // tell worker there is something to do
                    comm.send<int>(worker, tag_status, status_work);

                    comm.send<int>(worker, tag_dlzka_hesla, dlzky_hesiel[k]);
                    comm.send<string>(worker, tag_ciphertext, ciphertext);
                    comm.send<string>(worker, tag_plaintext, plaintext);
                    comm.send<int>(worker, tag_poradove_cislo, i);
                }
            }
        }
        // when everything is done, shutdown workers
        for (int i = 1; i < app.size(); i++) {
            int worker;
            comm.recv<int>(mpi::any_source, tag_worker, worker);
            comm.send<int>(worker, tag_status, status_exit);
        }

    } else {
        // worker node, master node is 0
        while (1) {
            int status;

            // tell master we are free and wait for master for something to do or shutdown
            comm.sendrecv<int>(0, tag_worker, app.rank(), 0, tag_status, status);

            if (status != status_work) {
                // nothing to do, exit
                break;
            }

            int dlzka_hesla, i;
            string ciphertext, plaintext;
            comm.recv<int>(0, tag_dlzka_hesla, dlzka_hesla);
            comm.recv<string>(0, tag_ciphertext, ciphertext);
            comm.recv<string>(0, tag_plaintext, plaintext);
            comm.recv<int>(0, tag_poradove_cislo, i);

            if (dlzka_hesla <= 20)
                horolezec(dlzka_hesla, ciphertext, plaintext, fitness, 100000, &subory, &landscape, i);
            else
                horolezec(dlzka_hesla, ciphertext, plaintext, fitness, 50000, &subory, &landscape, i);
        }
    }

    return 0;
}
