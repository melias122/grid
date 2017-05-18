// Project HelloGrid
//
// nodes defines number of nodes to use
// ppn defines number of proccesors to use
// total cores = nodes * ppn
// nodes = 2
// ppn = 2
//
// queue defines queue for this project
// available queues are: serial, parallel, debug, gpu
// queue = debug
//
// walltime defines time to run on grid. Format is hh:mm:ss
// walltime = 0:01:00
//
// Above variables are used for ../HelloGrid.pbs
// Edit them as needed, but do not delete them!
// Notice that gpus are not supported yet.

#include <iostream>

#include "mpi/App.h"

using namespace std;

int main(int argc, char **argv)
{
    MpiApp app(argc, argv);
    if (app.rank() == 0) {
        string msg;
        for (int i = 1; i < app.size(); i++) {
            app.recv(i, 0, msg);
            println(msg);
        }
    } else {
        string msg("hello my number is " + to_string(Rand.Int(0, 100)));
        app.send(0, 0, msg);
    }
    return 0;
}
