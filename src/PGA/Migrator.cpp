#include "Migrator.h"

#include <iostream>

using namespace std;

map<int, set<tuple<int, Migration::Type>>> Migrator::p_senderMigrations = {};
map<int, set<int>> Migrator::p_receiverMigrations = {};

void MpiMigrator::migrate(int senderId, int itteration, Population &population)
{
    if ((p_migrationTime % itteration) == 0) {

        m_sendRequest.clear();

        // posle sa populacia
        for (const tuple<int, Migration::Type> &s : p_senderMigrations[senderId]) {
            mpi::request req = comm.isend<Chromosome>(get<0>(s), 0, population[rand() % population.size()]);
            m_sendRequest.push_back(req);
        }

        // prijme sa migrovana populacia
        for (const int &id : p_receiverMigrations[senderId]) {
            population.push_back(Chromosome());
            mpi::request req = comm.irecv<Chromosome>(id, 0, population.back());
            m_sendRequest.push_back(req);
        }

        // cakanie na dokoncenie migracii
        mpi::wait_all(m_sendRequest.begin(), m_sendRequest.end());
    }
}
