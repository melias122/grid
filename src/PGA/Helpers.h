#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include <stdlib.h>
#include <time.h>

const char abcChars[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

namespace Helpers {

using namespace std;

static bool readFile(string& content, string path)
{
    ifstream ifs(path);
    if (!ifs.is_open()) {
        perror(path.c_str());
        return false;
    }
    content.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    ifs.close();
    return true;
}

// https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
static vector<vector<int> > comb(int N, int K)
{
    vector<vector<int> > retVal;
    string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
        vector<int> pair;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) {
                pair.push_back(i);
            }
        }
        retVal.push_back(pair);
    } while (prev_permutation(bitmask.begin(), bitmask.end()));

    return retVal;
}
}
#endif // HELPERS_H_INCLUDED
