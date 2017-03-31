#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

const char abcChars[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

namespace Helpers
{

static string rndAbcPermutation()
{
    string perm(26, 0);
    for (int i = 0; i < perm.size(); i++) {
        perm[i] = abcChars[i];
    }
    random_shuffle(begin(perm), end(perm));
    return perm;
}

static string readFile(string path)
{
    string content;
    ifstream ifs(path);
    if (!ifs.is_open()) {
        throw invalid_argument("could not open file: " + path);
    }
    content.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    ifs.close();
    return content;
}

// https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
static vector<vector<int>> comb(int N, int K)
{
    vector<vector<int>> retVal;
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
