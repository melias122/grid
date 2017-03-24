#ifndef GA_H
#define GA_H

#include "Cipher.h"
#include "Fitness.h"
#include "Migrator.h"
#include "SchemeGA.h"

class GA {
public:
    GA();

    SchemeGA* GetScheme() { return scheme; }
    void SetScheme(SchemeGA* val) { scheme = val; }

    void init(SchemeGA* sch, Cipher* c, Fitness* f);
    void setMigrator(Migrator* m);
    void start();
    Population applySelGenOp(SelGenOp& op, const Population& subPop);

    int getID() { return id; }

protected:
    int id{ 0 };
    Population population;
    SchemeGA* scheme;
    Cipher* cipher;
    Fitness* fitness;
    Migrator* migrator = nullptr;
};

#endif // GA_H
