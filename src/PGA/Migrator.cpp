#include "Migrator.h"

#include <iostream>

using namespace std;

map<int, set<tuple<int, Migration::Type>>> Migrator::p_senderMigrations = {};
map<int, set<int>> Migrator::p_receiverMigrations = {};

void MpiMigrator::migrate(int senderId, int itteration, Population &population)
{
    if ((p_migrationTime % itteration) == 0) {

        m_sendRequest.clear();

        // vykona sa migracia
        for (const tuple<int, Migration::Type> &s : p_senderMigrations[senderId]) {
            mpi::request req = comm.isend<Chromosome>(get<0>(s), 0, population[rand() % population.size()]);
            m_sendRequest.push_back(req);
        }

        for (const int &id : p_receiverMigrations[senderId]) {
            Chromosome ch;
            comm.recv<Chromosome>(id, 0, ch);
            population.push_back(ch);
        }

        mpi::wait_all(m_sendRequest.begin(), m_sendRequest.end());
    }
}
