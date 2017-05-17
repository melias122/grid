#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Helpers
{

static std::string readFile(std::string path)
{
    std::string content;
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        throw std::invalid_argument("could not open file: " + path);
    }
    content.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    ifs.close();
    return content;
}

// https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
static std::vector<std::vector<int>> comb(int N, int K)
{
    std::vector<std::vector<int>> retVal;
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
        std::vector<int> pair;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]) {
                pair.push_back(i);
            }
        }
        retVal.push_back(pair);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return retVal;
}
}
#endif // HELPERS_H_INCLUDED
