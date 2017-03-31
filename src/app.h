#ifndef APP_H
#define APP_H

#include <boost/mpi.hpp>
#include <cstdlib>
#include <ctime>

namespace mpi = boost::mpi;

class MpiApp : public mpi::environment
{
public:
    MpiApp()
    {
        srand(time(0) + rank());
    }

    MpiApp(int &argc, char **&argv)
        : mpi::environment(argc, argv)
    {
        srand(time(0) + rank());
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

#endif // APP_H
