// Project PGA
//
// nodes defines number of nodes to use
// ppn defines number of proccesors to use
// total cores = nodes * ppn
// nodes = 8
// ppn = 12
//
// queue defines queue for this project
// available queues are: serial, parallel, debug, gpu
// queue = parallel
//
// walltime defines time to run on grid. Format is hh:mm:ss
// walltime = 200:00:00
//
// Above variables are used for ../PGA.pbs
// Edit them as needed, but do not delete them!
// Notice that gpus are not supported yet.

// ../PGA.pbs is not used for this project
// instead ../run.sh is used which generates
// all needed .pbs files

#include "MpiApp.h"
#include "PGA.h"
#include "Schemes.h"
#include "Topology.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <fstream>
#include <string>

using namespace std;

// generator chromozomov
string alphabet = "abcdefghijklmnopqrstuvwxyz";

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
    L1DistanceBigrams *fitness = L1DistanceBigrams::fromFile(dir + "fitness/2.csv");

    // operacie
    for (const auto &schemaId : vector<char>{ 'J', 'C', 'E' }) {

        // velkost populacie
        for (int popsize : vector<int>{ 10, 20, 50, 100 }) {

            // pocet textov pre dlzku
            for (int text = 1; text <= 75; text++) {

                // dlzka textu
                for (int textSize = 50; textSize <= 2000; textSize += 50) {

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

                    LRU::Cache<Genes, double> cache(32768 * 2);

                    // topologia
                    //                    for (const auto &topologyId : { 'b', 'd', 'e', 'f' }) {

                    // migracny cas
                    for (auto migrationTime : vector<int>{ 1000, 5000, 10000 }) {

                        MpiMigrator migrator(migrationTime);

                        bool ok = _topology[topologyId](migrator, comm.size() - 1);
                        if (!ok) {
                            cerr << "error: topology" << endl;
                            continue;
                        }

                        // vytvor schemu
                        Scheme scheme(30000, popsize, &generator, &cipher, fitness, &migrator);
                        scheme.cache = &cache;

                        // pridaj operacie
                        scheme.replaceOperations(_schema[schemaId](popsize));

                        // spusti geneticky algoritmus
                        Population pop = GeneticAlgorithm::run(comm.rank(), scheme);

                        if (comm.rank() == 0) {

                            // zozbieranie vysledkov na vyhodnotenie
                            switch (topologyId) {
                            case 'e':
                            case 'f':
                                break;
                            default:
                                for (int i = 0; i < comm.size() - 2; i++) {
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

                            // textsize poradie match  popsize schemaId topologyId migrationTime
                            // 50       1       41     10      J        e          1000
                            println(textSize
                                << " " << text
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
                }
            }
        }
    }
}

// 'b', 'd', 'e', 'f'
// ./app [topology]
int main(int argc, char **argv)
{
    MpiApp app(argc, argv);

    if (app.size() < 3) {
        println("we need at least 3 nodes");
        return 1;
    }

    if (argc != 2) {
        println("topology was not set");
        return 1;
    }

    if (app.rank() == app.size() - 1) {
        return 0;
    }

    run(app.communicator(), "input/", *argv[1]);

    return 0;
}
