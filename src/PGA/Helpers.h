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

class Helpers {
public:
    static std::string readFile(std::string fName)
    {
        std::ifstream ifs;
        ifs.open(fName, std::ifstream::in);
        std::string content;
        content.assign((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));
        ifs.close();
        return content;
    }

    static std::vector<std::string> split(const std::string& s, char delim)
    {
        std::vector<std::string> elems;
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    static std::vector<int> toIntVec(std::vector<std::string>& tokens)
    {
        std::vector<int> retVal;
        std::string::size_type sz; // alias of size_t
        for (int i = 0; i < tokens.size(); i++) {
            int i_dec = std::stoi(tokens[i], &sz);
            retVal.push_back(i_dec);
        }
        return retVal;
    }

    static void readReferenceMonograms(double* out)
    {
        std::string fc = Helpers::readFile("input/fr_1.csv");
        std::stringstream ss;
        ss.str(fc);
        std::string item;
        std::string::size_type sz;
        while (std::getline(ss, item, '\n')) {
            std::string first;
            std::string second;
            std::stringstream linestream(item);
            getline(linestream, first, ',');
            getline(linestream, second, ',');
            out[first[0] - 'a'] = (double)std::stod(second, &sz);
        }
    }

    static void readReferenceBigrams(double** out)
    {
        std::string fc = Helpers::readFile("input/fr_2.csv");
        std::stringstream ss;
        ss.str(fc);
        std::string item;
        std::string::size_type sz;
        while (std::getline(ss, item, '\n')) {
            std::string first;
            std::string second;
            std::stringstream linestream(item);
            getline(linestream, first, ',');
            getline(linestream, second, ',');
            out[first[0] - 'a'][first[1] - 'a'] = (double)std::stod(second, &sz);
        }
    }

    static void readReferenceTrigrams(double*** out)
    {
        std::string fc = Helpers::readFile("input/fr_3.csv");
        std::stringstream ss;
        ss.str(fc);
        std::string item;
        std::string::size_type sz;
        while (std::getline(ss, item, '\n')) {
            std::cout << "line" << item << "\n";
            std::string first;
            std::string second;
            std::stringstream linestream(item);
            getline(linestream, first, ',');
            getline(linestream, second, ',');
            out[first[0] - 'a'][first[1] - 'a'][first[2] - 'a'] = (double)std::stod(second, &sz);
        }
    }

    // https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
    static std::vector<std::vector<int> > comb(int N, int K)
    {
        std::vector<std::vector<int> > retVal;
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
};
#endif // HELPERS_H_INCLUDED
