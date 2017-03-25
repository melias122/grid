#include "Migrator.h"
#include "Helpers.h"
#include <iostream>

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
Migrator::Migrator(){

};

void Migrator::buildTopology(int sender, Migrate send, int receiver,
    Migrate replace)
{
    MigrationModel mms;
    mms.gaId = receiver;
    mms.migrationType = replace;

    if (senders.find(sender) == senders.end()) {
        std::vector<MigrationModel> tmp;
        senders[sender] = tmp;
    }
    (*senders.find(sender)).second.push_back(mms);

    MigrationModel mmr;
    mmr.gaId = sender;
    mmr.migrationType = send;

    if (receivers.find(receiver) == receivers.end()) {
        std::vector<MigrationModel> tmp;
        receivers[receiver] = tmp;
    }
    (*receivers.find(receiver)).second.push_back(mmr);
}

void Migrator::requestMigration(int senderID, const Population &toSend,
    Population &toReceive)
{
    // zatial test cout -> mal by podla ID poslat zoznam chromosomov v nejakom
    // formate co sa da poslat medzi
    // MPI nodes ... preto tu nenechavam ani GA*, ale gaID
    std::cout << "sender id: " << senderID << "\n";
    std::vector<MigrationModel> mList = senders[senderID];
    std::cout << "sending to id: ";
    for (int i = 0; i < mList.size(); i++) {
        // Helpers::printChromosome(toSend);
        std::cout << mList[i].gaId << "\t mType:" << mList[i].migrationType << "\n";
    }
}

void Migrator::receive(int sender, int receiver, Population toReceive)
{
    // ?
}

void Migrator::send(int sender, int receiver, Population toSend)
{
    // ?
}
