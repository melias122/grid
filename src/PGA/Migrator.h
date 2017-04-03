#ifndef MIGRATOR_H
#define MIGRATOR_H

#include "Chromosome.h"

#include <boost/mpi/communicator.hpp>
#include <map>
#include <set>

namespace mpi = boost::mpi;

class Migration
{
public:
    enum class Type {
        Random,
        Best,
        Worst,
        Tournament
    };

    Migration(int receiverId, Type type, int choose)
        : m_receiverId{ receiverId }
        , m_type{ type }
        , m_choose{ choose }
    {
    }

    int receiverId() const { return m_receiverId; }
    Population select(Population &p) const;

private:
    int m_receiverId;
    Type m_type;
    int m_choose;

    friend class Migrator;
    friend bool operator<(const Migration &l, const Migration &r);
    friend std::ostream &operator<<(std::ostream &os, const Migration &m);
};

class Migrator
{
public:
    Migrator(int migrationTime)
        : p_migrationTime{ migrationTime }
    {
    }
    ~Migrator() {}

    virtual void migrate(int senderId, int itteration, Population &population) = 0;

    // migracia typu sender <-> receiver
    static void addMigration(int senderId, int receiverId, Migration::Type type, int chooseMax)
    {
        p_senderMigrations[senderId].emplace(receiverId, type, chooseMax);
        //        p_senderMigrations[receiverId].emplace(senderId, type, chooseMax);

        p_receiverMigrations[receiverId].insert(senderId);
        //        p_receiverMigrations[senderId].insert(receiverId);
    }

    void printMigrations();

protected:
    static std::map<int, std::set<Migration>> p_senderMigrations;
    static std::map<int, std::set<int>> p_receiverMigrations;

    int p_migrationTime{ 0 };
};

class MpiMigrator : public Migrator
{
public:
    MpiMigrator(int migrationTime)
        : Migrator(migrationTime)
    {
    }
    void migrate(int senderId, int itteration, Population &population) override;

private:
    mpi::communicator comm;
};

#endif
