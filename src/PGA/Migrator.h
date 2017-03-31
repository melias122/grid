#ifndef MIGRATOR_H
#define MIGRATOR_H

#include "Chromosome.h"

#include <boost/mpi/communicator.hpp>
#include <map>
#include <set>
#include <tuple>

namespace mpi = boost::mpi;

enum class MigrationType {
    Random,
    Best,
    Worst
};

class Migrator
{
public:
    ~Migrator() {}

    virtual void migrate(int senderId, int itteration, Population &Population) = 0;

    // migracia typu sender <-> receiver
    static void addMigration(int senderId, int receiverId, MigrationType type)
    {
        p_senderMigrations[senderId].insert(std::make_tuple(receiverId, type));
        p_senderMigrations[receiverId].insert(std::make_tuple(senderId, type));

        p_receiverMigrations[receiverId].insert(senderId);
        p_receiverMigrations[senderId].insert(receiverId);
    }

    // nastavi kedy sa ma vykonat migracia, kazdu n-tu iteraciu (nthItteration)
    void setMigrationTime(int nthItteration) { p_migrationTime = nthItteration; }

protected:
    static std::map<int, std::set<std::tuple<int, MigrationType>>> p_senderMigrations;
    static std::map<int, std::set<int>> p_receiverMigrations;

    int p_migrationTime{ 0 };
};

class MpiMigrator : public Migrator
{
public:
    void migrate(int senderId, int itteration, Population &population) override;

private:
    mpi::communicator comm;
};

#endif
