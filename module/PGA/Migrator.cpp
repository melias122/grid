#include "Migrator.h"

#include "utils/Debug.h"
#include "SelectElitism.h"
#include "SelectRandom.h"
#include "SelectTournament.h"
#include "SelectWorst.h"

#include <iostream>

using namespace std;

static map<Migration::Type, string> type_to_string = {
    { Migration::Type::Random, "Random" },
    { Migration::Type::Best, "Best" },
    { Migration::Type::Worst, "Worst" },
    { Migration::Type::Tournament, "Tournament" },
};

Population Migration::select(Population &p) const
{
    DBG_LOG("select " << type_to_string[m_type]);
    switch (m_type) {
    case Type::Best: {
        SelectElitism s(m_choose);
        return s.select(p);
    }

    case Type::Worst: {
        SelectWorst s(m_choose);
        return s.select(p);
    }

    case Type::Random: {
        SelectRandom s(m_choose);
        return s.select(p);
    }

    case Type::Tournament: {
        SelectTournament s(m_choose);
        return s.select(p);
    }

    default:
        throw invalid_argument("Migration::select ivalid argument " + to_string(int(m_type)));
    }
}

bool operator<(const Migration &l, const Migration &r)
{
    return l.m_receiverId < r.m_receiverId;
}

ostream &operator<<(ostream &os, const Migration &m)
{
    return os << "receiver=" << m.m_receiverId << ", type=" << type_to_string[m.m_type] << ", choose=" << m.m_choose;
}

void Migrator::printMigrations()
{
    cout << "senders = [" << endl;
    for (auto i : p_senderMigrations) {
        cout << get<0>(i) << " -> "
             << " { ";
        for (auto m : get<1>(i)) {
            cout << "( " << m << " )";
        }
        cout << "}" << endl;
    }
    cout << "]" << endl;

    cout << "receivers = [" << endl;
    for (auto i : p_receiverMigrations) {
        cout << get<0>(i) << " <- "
             << " { ";
        for (auto id : get<1>(i)) {
            cout << "( sender=" << id << ") ";
        }
        cout << "}" << endl;
    }
    cout << "]" << endl;
}

void MpiMigrator::migrate(int senderId, int itteration, Population &p)
{
    if (p_migrationTime <= 0) {
        return;
    }

    if ((itteration % p_migrationTime) == 0) {

        vector<mpi::request> request;

        // posle sa populacia
        for (const Migration &m : p_senderMigrations[senderId]) {
            Population pop = m.select(p);
            DBG_LOG(senderId << " -> " << m.receiverId() << " = " << pop);

            mpi::request r = comm.isend<Population>(m.receiverId(), 0, pop);
            request.push_back(r);
        }

        // prijme sa migrovana populacia
        for (const int &id : p_receiverMigrations[senderId]) {
            Population pop;
            comm.recv<Population>(id, 0, pop);
            append(p, pop);

            DBG_LOG(senderId << "<- " << id << " = " << pop);
        }

        // cakanie na dokoncenie migracii
        for (auto &req : request) {
            req.wait();
        }
    }
}
