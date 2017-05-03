#include "main.h"

#include "MpiApp.h"
#include "PGA.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <fstream>
#include <string>

unordered_map<char, topology_func *> _topology = {
    { 'b', &grid },
    { 'd', &ring },
    { 'e', &tree },
    { 'f', &tree2 },
};

unordered_map<char, schema_func *> _schema = {
    { 'C', &schemaC },
    { 'E', &schemaE },
    { 'J', &schemaJ },
};

bool readFile(string path, string &content)
{
    ifstream ifs(path);
    if (!ifs.is_open()) {
        cerr << "could not open file: " + path << endl;
        return false;
    }
    content.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    ifs.close();
    return true;
}

void run(const mpi::communicator &comm, string dir, char topologyId)
{
    string ptx;
    ShuffleGenerator generator(alphabet);
    Fitness *fitness = L1DistanceBigrams::fromFile(dir + "fitness/2.csv");

    // dlzka textu
    for (int textSize = 50; textSize <= 2000; textSize += 50) {

        // pocet textov pre dlzku
        for (int text = 1; text <= 100; text++) {

            string ct, pt;

            // nacitaj ciphertext
            // ...
            // a zaroven aj plaintext pre porovnanie

            string path = dir + "ct/" + to_string(textSize) + "_" + to_string(text) + ".txt";
            if (!readFile(path, ct)) {
                continue;
            }

            path = dir + "pt/" + to_string(textSize) + "_" + to_string(text) + ".txt";
            if (!readFile(path, pt)) {
                continue;
            }

            Monoalphabetic cipher(ct);

            // velkost populacie
            for (int popsize : { 10, 20, 50, 100 }) {

                // operacie
                for (const auto &schemaId : { 'C', 'E', 'J' }) {

                    // topologia
                    //                    for (const auto &topologyId : { 'b', 'd', 'e', 'f' }) {

                    // migracny cas
                    for (auto migrationTime : { 1000, 5000, 10000 }) {

                        MpiMigrator migrator(migrationTime);

                        bool ok = _topology[topologyId](migrator, comm.size());
                        if (!ok) {
                            continue;
                        }

                        // vytvor schemu
                        Scheme scheme(50000, popsize, &generator, &cipher, fitness, &migrator);

                        // pridaj operacie
                        scheme.replaceOperations(_schema[schemaId](popsize));

                        // pred spustenim genetickeho algoritmu pockaj
                        // na vsetky ostatetne ostrovy
                        comm.barrier();

                        // spusti geneticky algoritmus
                        Population pop = GeneticAlgorithm::run(comm.rank(), scheme);

                        if (comm.rank() == 0) {

                            // zozbieranie vysledkov na vyhodnotenie
                            switch (topologyId) {
                            case 'e':
                            case 'f':
                                break;
                            default:
                                for (int i = 0; i < comm.size() - 1; i++) {
                                    Population others;
                                    comm.recv<Population>(mpi::any_source, 0, others);
                                    append(pop, others);
                                }
                                break;
                            }

                            // vyber najlepsieho
                            sort(pop.begin(), pop.end(), Chromosome::byBestScore());

                            // desifruj ct
                            cipher.decrypt(pop[0].genes(), ptx);

                            // match rate s pt (% kolko znakov sa zhoduje)
                            int match = 0;
                            for (int i = 0; i < ptx.size(); i++) {
                                if (ptx[i] == pt[i]) {
                                    match++;
                                }
                            }

                            // textsize  match  popsize schemaId topologyId migrationTime
                            // 50         41     10     J        e          1000
                            println(ct.size()
                                << " " << match
                                << " " << popsize
                                << " " << schemaId
                                << " " << topologyId
                                << " " << migrationTime);

                        } else {

                            // v pripade stromovej struktury sa vyhodnocuje iba vrchol stromu
                            // inak sa posielaju data na vyhodnotenie do uzla 0
                            switch (topologyId) {
                            case 'e':
                            case 'f':
                                break;
                            default:
                                comm.send<Population>(0, 0, pop);
                                break;
                            }
                        }
                    }
                    //                    }
                }
            }
        }
    }
}

// 'b', 'd', 'e', 'f'
// ./app b dir/
int main(int argc, char **argv)
{
    MpiApp app(argc, argv);

    if (app.size() < 3) {
        printf("we need at least 3 nodes");
        return 1;
    }

    string dir("../project/PGA/input/");
    if (argc == 3) {
        dir = argv[2];
    }

    run(app.communicator(), dir, *argv[1]);

    return 0;
}
