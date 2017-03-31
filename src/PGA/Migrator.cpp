#include "Migrator.h"

#include <iostream>

using namespace std;

map<int, set<tuple<int, MigrationType>>> Migrator::p_senderMigrations;
map<int, set<int>> Migrator::p_receiverMigrations;

void MpiMigrator::migrate(int senderId, int itteration, Population &population)
{
    if ((p_migrationTime % itteration) == 0) {

        vector<mpi::request> request;

        // posle sa populacia
        for (const tuple<int, MigrationType> &s : p_senderMigrations[senderId]) {
            mpi::request r = comm.isend<Chromosome>(get<0>(s), 0, population[rand() % population.size()]);
            request.push_back(r);
        }

        // prijme sa migrovana populacia
        for (const int &id : p_receiverMigrations[senderId]) {
            population.push_back(Chromosome());
            mpi::request r = comm.irecv<Chromosome>(id, 0, population.back());
            request.push_back(r);
        }

        // cakanie na dokoncenie migracii
        mpi::wait_all(request.begin(), request.end());
    }
}
