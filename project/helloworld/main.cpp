#include "app.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    Application app(argc, argv);

    cout << "Hello"
         << " rank " << app.rank() << " of world size " << app.size() << endl;
    return 0;
}
