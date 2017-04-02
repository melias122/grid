#ifndef MPI_APP_H
#define MPI_APP_H

#include <boost/mpi.hpp>

#include "Debug.h"
#include "Random.h"

namespace mpi = boost::mpi;

class MpiApp : public mpi::environment
{
public:
    MpiApp()
    {
    }

    MpiApp(int &argc, char **&argv)
        : mpi::environment(argc, argv)
    {
    }

    int rank() { comm.rank(); }
    int size() { comm.size(); }
    const mpi::communicator &communicator() const { return comm; }

private:
    mpi::communicator comm;
};

using Application = MpiApp;

class Bruteforcer
{
public:
    ~Bruteforcer() {}

    // notice that procId count from 0
    // procId is always < nproc
    virtual void run(const mpi::communicator &c) = 0;
};

struct Runner {
    Runner() = delete;

    static void run(Bruteforcer *b)
    {
        MpiApp app;
        b->run(app.communicator());
    }
};

#endif // MPI_APP_H
