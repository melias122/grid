#include "Migrator.h"

#include <iostream>

using namespace std;
using namespace boost;

map<int, set<Migration>> Migrator::p_senderMigrations = {};
map<int, set<Migration>> Migrator::p_receiverMigrations = {};

Population MpiMigrator::migrate(int senderId, const Population &population)
{
    Population newpop;
    vector<mpi::request> requests;

    for (const Migration &m : p_senderMigrations[senderId]) {
        mpi::request req = comm.isend<Chromosome>(m.id, 0, population[rand() % population.size()]);
        requests.push_back(req);
    }

    for (const Migration &m : p_receiverMigrations[senderId]) {
        Chromosome ch;
        comm.recv<Chromosome>(m.id, 0, ch);
        newpop.push_back(ch);
    }

    mpi::wait_all(requests.begin(), requests.end());

    return newpop;
}
