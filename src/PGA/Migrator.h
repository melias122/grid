#ifndef MIGRATOR_H
#define MIGRATOR_H

#include "Chromosome.h"

#include <boost/mpi.hpp>
#include <map>
#include <set>
#include <tuple>

namespace mpi = boost::mpi;

struct Migration {
    enum class Type {
        None,
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
    Type type{ Type::None };
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
    static std::map<int, std::set<std::tuple<int, Migration::Type>>> p_senderMigrations;
    static std::map<int, std::set<int>> p_receiverMigrations;

    int p_migrationTime{ 0 };

public:
    virtual void migrate(int senderId, int itteration, Population &Population) = 0;

    // migracia typu sender <-> receiver
    static void addMigration(int senderId, int receiverId, Migration::Type type)
    {
        if (type == Migration::Type::None) {
            return;
        }

        p_senderMigrations[senderId].insert(std::make_tuple(receiverId, type));
        p_senderMigrations[receiverId].insert(std::make_tuple(senderId, type));

        p_receiverMigrations[receiverId].insert(senderId);
        p_receiverMigrations[senderId].insert(receiverId);
    }

    // nastavi kedy sa ma vykonat migracia, kazdu n-tu iteraciu (nthItteration)
    void setMigrationTime(int nthItteration) { p_migrationTime = nthItteration; }
};

class MpiMigrator : public Migrator
{
public:
    void migrate(int senderId, int itteration, Population &population) override;

private:
    mpi::communicator comm;

    std::vector<mpi::request> m_sendRequest;
};

#endif
