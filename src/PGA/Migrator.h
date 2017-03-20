#ifndef MIGRATOR_H
#define MIGRATOR_H

#include <vector>
#include <map>
#include "Chromosome.h"

enum Migrate {
    rnd, best, worst
};

struct MigrationModel {
    int gaId;
    Migrate migrationType;
};

class Migrator {
public:
    Migrator();

    void buildTopology(int senderID, Migrate send, int receiverID, Migrate replace);
    void requestMigration(int senderID, std::vector<Chromosome *> toSend, std::vector<Chromosome *>& toReceive);



private:
    std::map<int, std::vector<MigrationModel>> senders;
    std::map<int, std::vector<MigrationModel>> receivers;
    //
    void receive(int sender, int receiver, std::vector<Chromosome *> toReceive);
    void send(int sender, int receiver, std::vector<Chromosome *> toSend);

};

#endif 
