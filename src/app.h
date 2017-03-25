#ifndef APP_H
#define APP_H

#include <string>

class Application
{
public:
    Application() {}
    Application(int argc, char **argv);
    ~Application();

    int rank();
    int size();

private:
    int m_rank, m_size;
};

class Bruteforcer
{
public:
    ~Bruteforcer() {}

    // notice that procId count from 0
    // procId is always < nproc
    virtual void run(int procId, int nproc) = 0;
};

struct Runner {
    Runner() = delete;

    static void run(Bruteforcer *b)
    {
        Application app;
        b->run(app.rank(), app.size());
    }
};

void sendString(int dest, int tag, const std::string &s);
std::string recvString(int source, int tag);

// experimental communicator
template <typename T>
struct comm {
public:
    void send(int dest, int tag, const T &data, int size = 1);
    T recv(int source, int tag, int size = 1) const;
};

template struct comm<char>;
template struct comm<int>;

#endif // APP_H
