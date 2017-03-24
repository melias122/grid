#ifndef MIGRATOR_H
#define MIGRATOR_H

#include "Chromosome.h"
#include <map>
#include <vector>

enum Migrate { rnd,
    best,
    worst };

struct MigrationModel {
    int gaId;
    Migrate migrationType;
};

class Migrator {
public:
    Migrator();

    void buildTopology(int senderID, Migrate send, int receiverID,
        Migrate replace);
    void requestMigration(int senderID, const Population& toSend,
        Population& toReceive);

private:
    std::map<int, std::vector<MigrationModel> > senders;
    std::map<int, std::vector<MigrationModel> > receivers;
    //
    void receive(int sender, int receiver, Population toReceive);
    void send(int sender, int receiver, Population toSend);
};

#endif
