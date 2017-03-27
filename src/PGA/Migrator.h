#ifndef MIGRATOR_H
#define MIGRATOR_H

#include "Chromosome.h"

#include <boost/mpi.hpp>
#include <map>
#include <set>

struct Migration {
    enum class Type {
        Random,
        Best,
        Worst
    };

    Migration(Type type, int id)
        : type{ type }
        , id{ id }
    {
    }

    int id;
    Type type;
};

inline bool operator<(const Migration &a, const Migration &b)
{
    return a.id < b.id && a.type < b.type;
}

/**
 * Idea: pomocou buildTopology postupne inicializujeme topologiu, migracny
 * model, atd ...
 * GA, ked sa rozhodne o poslanie udajov, zavola requestMigration metodu - tu
 * bude treba synchronizacia,
 * poslu sa data (dostaneme celu populaciu z GA, a Migrator podla migracneho
 * modelu zabezpeci vyber chromozomov,
 * ktore treba poslat dalej; t.j. zo senders sa zisti kde vsade chceme poslat a
 * posleme)
 * A zaroven sa caka na prijatie novych (Migrator zabezpeci data z inych uzlov
 * ; t.j. z receivers dostaneme GA, ktore by mali dodat ich populacie).
 * Aby sme nemali deadlock s cakanim, treba nejak rozumne, napr kednie su data
 * tak idem dalej a skusim next ...
 */
class Migrator
{
protected:
    static std::map<int, std::set<Migration>> p_senderMigrations;
    static std::map<int, std::set<Migration>> p_receiverMigrations;

public:
    virtual Population migrate(int senderId, const Population &Population) = 0;

    static void addMigration(int senderId, const std::set<Migration> &migration)
    {
        p_senderMigrations[senderId].insert(migration.begin(), migration.end());

        for (const Migration &m : migration) {
            p_receiverMigrations[m.id].emplace(m.type, senderId);
        }
    }
};

class MpiMigrator : public Migrator
{
public:
    MpiMigrator(const boost::mpi::communicator &comm)
        : comm{ comm }
    {
    }
    Population migrate(int senderId, const Population &population) override;

private:
    boost::mpi::communicator comm;
};

#endif
