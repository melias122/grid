#include "app.h"

#include <iostream>

using namespace std;

// ring send
// first send 0 and receive from last
// next increment by 2
// ...

class ring_piece
{
public:
    ring_piece(int id)
        : id{ id }
    {
    }

    void run()
    {
        if (id == 0) {
            int data = 1;
            co.send(id + 1, 0, data);
            co.recv(id - 1, 0);
        } else {
            int i = co.recv(id - 1, 0);
            co.send(id + 1, 0, i + 2);
        }
    }

private:
    int id;
    comm<int> co;
};

int main(int argc, char **argv)
{
    Application app;

    ring_piece r(app.rank());
    r.run();

    return 0;
}
