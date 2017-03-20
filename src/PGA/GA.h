#ifndef GA_H
#define GA_H

#include <vector>
#include <fstream>
//#include <iostream>

#include "Chromosome.h"
#include "SchemeGA.h"
#include "Cipher.h"
#include "Fitness.h"
#include "Migrator.h"


class GA
{
    public:
        GA();

        SchemeGA* GetScheme() { return scheme; }
        void SetScheme(SchemeGA* val) { scheme = val; }

        
        void init(SchemeGA* sch, Cipher* c, Fitness* f);
        void setMigrator(Migrator* m);
        void start();
        std::vector<Chromosome *> applySelGenOp(SelGenOp& op, std::vector<Chromosome *>& subPop);
        
        int getID(){
            return this->id;
        }
    protected:
        int id;
        std::vector<Chromosome *> population;
        SchemeGA* scheme; 
        Cipher *cipher;
        Fitness *fitness;
        Migrator *migrator = nullptr;

};

#endif // GA_H
