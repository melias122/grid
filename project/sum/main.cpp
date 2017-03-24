#include "app.h"

#include <iostream>
#include <vector>

using namespace std;

class sum_proc {
public:
    sum_proc(int rank, int world_size)
        : rank{ rank }
        , world_size{ world_size }
    {
        for (int i = 0; i < 1000; i++) {
            values.push_back(i);
        }
    }

    void run()
    {
        if (rank == 0) {
            master();
        } else {
            worker();
        }
    }

private:
    void master()
    {
        if (rank == 0) {

            int sum = 0;

            for (int i = 1; i < world_size; i++) {
                sum += co.recv(i, 0);
            }

            cout << "total sum " << sum << endl;
        }
    }

    void worker()
    {
        if (rank != 0) {
            int from = 0;
            int range = (int)((values.size() / ((double)world_size - 1)) + 1.0);

            int sum = 1;
            //			sleep(5);
            co.send(0, 0, sum);
        }
    }

    int rank, world_size;
    comm<int> co;
    vector<int> values;
};

int main(int argc, char** argv)
{
    Application app;

    sum_proc p(app.rank(), app.size());
    p.run();

    return 0;
}
