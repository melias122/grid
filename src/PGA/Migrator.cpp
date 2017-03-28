#include "Migrator.h"

#include <iostream>

using namespace std;
using namespace boost::mpi;

map<int, set<tuple<int, Migration::Type>>> Migrator::p_senderMigrations = {};
map<int, set<int>> Migrator::p_receiverMigrations = {};

Population MpiMigrator::migrate(int senderId, const Population &population)
{
    Population newpop;
    vector<request> requests;

    for (const tuple<int, Migration::Type> &s : p_senderMigrations[senderId]) {
        request req = comm.isend<Chromosome>(get<0>(s), 0, population[rand() % population.size()]);
        requests.push_back(req);
    }

    for (const int &id : p_receiverMigrations[senderId]) {
        Chromosome ch;
        comm.recv<Chromosome>(id, 0, ch);
        newpop.push_back(ch);
    }

    wait_all(requests.begin(), requests.end());

    return newpop;
}
