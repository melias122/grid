// Project ga
//
// nodes defines number of nodes to use
// ppn defines number of proccesors to use
// total cores = nodes * ppn
// nodes = 1
// ppn = 4
//
// queue defines queue for this project
// available queues are: serial, parallel, debug, gpu
// queue = parallel
//
// walltime defines time to run on grid. Format is hh:mm:ss
// walltime = 200:00:00
//
// Above variables are used for ../ga.pbs
// Edit them as needed, but do not delete them!
// Notice that gpus are not supported yet.

#include "PGA/PGA.h"
#include "cipher/Monoalphabetic.h"
#include "fitness/L1.h"
#include "mpi/App.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// generator chromozomov
string alphabet = "abcdefghijklmnopqrstuvwxyz";

enum Node {
    master,
    writer
};

class Data
{
public:
    Data(int _workerId = 0)
        : workerId{ _workerId }
    {
    }

    int status, itterations, popsize, textsize, match, workerId;
    string plaintext, ciphertext, schemaId;

private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &status;
        ar &itterations;
        ar &popsize;
        ar &textsize;
        ar &match;
        ar &workerId;
        ar &plaintext;
        ar &ciphertext;
        ar &schemaId;
    }
};

bool readFile(string path, string &content)
{
    ifstream ifs(path);
    if (!ifs.is_open()) {
        println("could not open file: " + path);
        return false;
    }
    content.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    ifs.close();
    return true;
}

void run_master(const mpi::communicator &comm, string dir)
{
    for (int itterations : { 10000, 50000 }) {

        // velkost populacie
        for (int popSize : { 10, 20, 50, 100 }) {

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
                        println("error: can't read " << path);
                        continue;
                    }

                    path = dir + "pt/" + to_string(textSize) + "_" + to_string(text) + ".txt";
                    if (!readFile(path, pt)) {
                        println("error: can't read " << path);
                        continue;
                    }

                    // mpi komunikacia
                    Data data;
                    comm.recv<Data>(mpi::any_source, 0, data);

                    data.status = 1;
                    data.itterations = itterations;
                    data.popsize = popSize;
                    data.plaintext = pt;
                    data.ciphertext = ct;
                    data.textsize = ct.size();

                    // oznam workerovi ze ma prijat pracu
                    comm.send<Data>(data.workerId, 1, data);
                }
            }
        }
    }

    Data exit;
    for (int i = 0; i < comm.size(); i++) {
        if (i == master || i == writer)
            continue;

        comm.recv<Data>(mpi::any_source, 0, exit);

        exit.status = 0;
        comm.send<Data>(exit.workerId, 1, exit);
    }

    exit.status = 0;
    comm.send<Data>(writer, 2, exit);
}

void run_writer(const mpi::communicator &comm)
{
    while (1) {

        Data data;
        comm.recv<Data>(mpi::any_source, 2, data);

        if (!data.status) {
            cerr << "writer: exiting" << endl;
            break;
        }

        // text size; match; itterations; initial population; schema ID
        // 50       ; 41   ; 10000      ; 10                ; J
        println(data.textsize << " " << data.match << " " << data.itterations << " " << data.popsize << " " << data.schemaId);
    }
    cout.flush();
}

void run_worker(int id, const mpi::communicator &comm, string dir)
{
    string ptx;
    ShuffleGenerator generator(alphabet);
    Fitness *fitness = L1DistanceBigrams::fromFile(dir + "fitness/2.csv");

    unordered_map<string, schema_func *> operationSchema = {
        { "A", &schemaA },
        { "B", &schemaB },
        { "C", &schemaC },
        { "D", &schemaD },
        { "E", &schemaE },
        { "F", &schemaF },
        { "G", &schemaG },
        { "H", &schemaH },
        { "I", &schemaI },
        { "J", &schemaJ },
    };

    while (1) {

        Data data(id);

        // tell master we are free and wait for master for something to do or shutdown
        comm.sendrecv<Data>(Node::master, 0, data, Node::master, 1, data);

        if (!data.status) {
            cerr << "worker: exiting " << id << endl;
            break;
        }

        string pt = data.plaintext;
        data.plaintext.clear();

        Monoalphabetic cipher(data.ciphertext);
        data.ciphertext.clear();

        // vytvor schemu
        Scheme scheme(data.itterations, data.popsize, &generator, &cipher, fitness);

        for (const auto &os : operationSchema) {

            data.schemaId = os.first;

            // pridaj operacie
            scheme.replaceOperations(os.second(data.popsize));

            // spusti geneticky algoritmus
            auto population = GeneticAlgorithm::run(id, scheme);

            // vyhodnot iteraciu
            // ...
            // vyber najlepsieho
            Chromosome &best = population[0];

            // desifruj ct
            scheme.cipher->decrypt(best.genes(), ptx);

            // match rate s pt (% kolko znakov sa zhoduje)
            data.match = 0;
            for (int i = 0; i < ptx.size(); i++) {
                if (ptx[i] == pt[i]) {
                    data.match++;
                }
            }

            // posli na zapis
            comm.send<Data>(Node::writer, 2, data);
        }
    }
}

int main(int argc, char **argv)
{
    MpiApp app(argc, argv);
    string dir("input/");

    if (app.rank() == Node::master)
        run_master(app.communicator(), dir);
    else if (app.rank() == Node::writer)
        run_writer(app.communicator());
    else
        run_worker(app.rank(), app.communicator(), dir);

    return 0;
}
