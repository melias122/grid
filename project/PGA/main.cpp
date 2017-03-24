/*
 * File:   main.cpp
 * Author: Jugin
 *
 * Created on March 2, 2017, 2:17 PM
 */

#include "Chromosome.h"
#include "Cipher.h"
#include "Fitness.h"
#include "FitnessL1.h"
#include "GA.h"
#include "GeneticOperation.h"
#include "GeneticOperationMutation.h"
#include "GeneticOperationMutationSwap.h"
#include "GeneticOperationMutationSwapAll.h"
#include "Helpers.h"
#include "SchemeGA.h"
#include "SelectElitism.h"
#include "SelectRandom.h"
#include "SelectTournament.h"
#include "SelectTournament.h"

#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <thread> /*threading*/
#include <time.h> /* time */

using namespace std;

#define println(msg) cout << msg << endl

/*
 *
 */
GA* GATest()
{
    Cipher* c = new Cipher;
    c->loadCipherText(
        "/home/melias122/code/grid/project/PGA/input/177_1000_num.txt");
    //	c->decrypt();
    // vector<int> CipherText = c->getCipherText();
    Fitness* f = new FitnessL1(2);

    SchemeGA* scheme = new SchemeGA(10000, 1000, 50);

    SelGenOp sg0; // pick the best one without any changes
    sg0.sel = new SelectElitism(1);
    sg0.op = new GeneticOperation(); // do nothing
    scheme->addToSchema(sg0);

    SelGenOp sg1; // pick the best one and swap
    sg1.sel = new SelectElitism(1);
    sg1.op = new GeneticOperationMutationSwap(
        1); // new GeneticOperationMutation(0.01f); //new
    // GeneticOperationMutationSwapAll();
    scheme->addToSchema(sg1);

    SelGenOp sg2; // pick 18 with tournament select without any changes
    sg2.sel = new SelectTournament(18);
    sg2.op = new GeneticOperation(); // do nothing
    scheme->addToSchema(sg2);

    // EXMAPLE TO ADD ADITIONAL OPERATIONS IN CHAIN ...
    //    SelGenOp sg1Next; // pick the best one and rnd change
    //    sg1Next.sel = new SelectElitism(1);
    //    sg1Next.op = new GeneticOperationMutation(0.05); //new
    //    GeneticOperationMutationSwapAll();
    //    sg1.next = &sg1Next;

    println("GA");

    GA* ga = new GA();
    ga->init(scheme, c, f);
    return ga;
}

void PGATest(vector<GA*>& gaPool)
{
    println("PGATest started");

    Migrator* mig = new Migrator();
    println("initialising migrator.");

    for (int i = 0; i < gaPool.size(); i++) {
        GA* ga = gaPool[i];
        ga->setMigrator(mig);
        if (i > 0) {
            GA* gaPrev = gaPool[i - 1];
            Migrate best = best;
            Migrate worst = worst;

            mig->buildTopology(gaPrev->getID(), best, ga->getID(), worst);
        }
    }
    cout << "starting gas.\n";

    vector<thread> tl;
    for (int i = 0; i < gaPool.size(); i++) {
        GA* ga = gaPool[i];
        tl.emplace_back(&GA::start, ga);
    }

    cout << "join.\n";

    for (int i = 0; i < tl.size(); i++) {
        tl[i].join();
    }

    cout << "function end.\n";
}

void mutationTest()
{
    Chromosome c;
    println(c);

    Population p;
    p.push_back(c);

    double mutationProbability = 0.05;

    for (int i = 0; i < p.size(); i++) {
        Chromosome& c = p[i];
        for (int g = 0; g < c.size(); g++) {
            double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

            println("prob: " << r);
            if (r < mutationProbability) {
                println("less than: " << mutationProbability);

                int rnd = rand() % sizeof(abcChars);
                println("index: " << g);

                char newChar = abcChars[rnd];
                println("to: : " << newChar);

                c.genes()[g] = newChar;
                println(c);
            }
        }
    }
}

void swapAllTest()
{
    Chromosome c;
    println(c);

    Population pop;
    pop.push_back(c);
    vector<vector<int> > comb = Helpers::comb(pop[0].size(), 2);

    Population allSwaps;
    for (int p = 0; p < pop.size(); p++) {
        for (int i = 0; i < comb.size(); i++) {
            vector<int> toSwap = comb[i];
            cout << toSwap[0] << "," << toSwap[1] << "\n";
            int a = toSwap[0];
            int b = toSwap[1];
            println(pop[p]);
            Chromosome chrm = pop[p];
            cout << "before:\n";
            println(chrm);
            swap(chrm.genes()[a], chrm.genes()[b]);
            cout << "after:\n";
            println(chrm);
            allSwaps.push_back(chrm);
        }
    }
    for (int i = 0; i < pop.size(); i++) {
        println(pop.at(i));
    }
}

void sortTest()
{
    Cipher cipher;
    cipher.loadCipherText("input/177_1000_num.txt");
    Fitness* fitness = new FitnessL1(2);

    Population v;
    for (int i = 0; i < 15; i++) {
        Chromosome c;
        v.push_back(c);
        string txt = cipher.decrypt(c.genes());
        double score = fitness->evaluate(txt);
        c.setScore(score);
    }

    for (int i = 0; i < 15; i++) {
        println(v[i].score());
    }

    //	sort(v.begin(), v.end(), Chromosome::PointerCompare());
    //	cout << "sorted:\n";

    for (int i = 0; i < 15; i++) {
        println(v[i].score());
    }
}

void vectorTest()
{
    Chromosome c, c2, c3;
    println(c);
    println(c2);
    println(c3);

    Population chv;
    chv.push_back(c);
    GeneticOperationMutationSwap* gs = new GeneticOperationMutationSwap();
    gs->apply(chv);
    println(chv[0]);

    vector<char> tmp;
    for (int i = 0; i < 26; i++) {
        tmp.push_back(i + 'a');
    }
    random_shuffle(tmp.begin(), tmp.end());
    for (int i = 0; i < 26; i++) {
        cout << tmp[i] << " ";
    }
    cout << "\n";
    swap(tmp[0], tmp[1]);
    for (int i = 0; i < 26; i++) {
        cout << tmp[i] << " ";
    }
    cout << "\n";

    int a = 0; // rand() % c->GetLength();
    int b = 1; // rand() % c->GetLength();
    cout << a << "\n";
    cout << b << "\n";

    auto ex = c.genes();
    swap(ex[a], ex[b]);
    // iter_swap(ex.begin() + position, ex.begin() + nextPosition);

    println(c);
}

int main(int argc, char** argv)
{

    vector<GA*> gaPool;
    for (int i = 0; i < 10; i++) {
        GA* ga = GATest();
        cout << ga->getID() << " created.\n";
        gaPool.push_back(ga);
    }
    // uncomment to PGA test:
    PGATest(gaPool);

    // uncomment to GA test
    //    gaPool[0]->start();

    return 0;
}
