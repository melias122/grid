#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <vector>
#include <string>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

#include <stdlib.h>
#include <time.h>

#include "Chromosome.h"

#define SWAP(a, b) a = a + b - (b = a)
const int abcLength = 26;
const char abcChars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

class Helpers {
public:

    static void printChromosome(Chromosome *chrm) {
        std::vector<char> * genes = chrm->GetGenes();
        for (int i = 0; i < chrm->GetLength(); i++) {
            std::cout << genes->at(i) << "";
        }
        std::cout << "\n";
    }

    static void printChromosome(Chromosome *chrm, std::ofstream* os) {
        std::vector<char> * genes = chrm->GetGenes();
        for (int i = 0; i < chrm->GetLength(); i++) {
            (*os) << genes->at(i) << "";
        }
        (*os) << "\n";
    }

    static std::vector<Chromosome *> deepCopy(std::vector<Chromosome *>& in) {
        std::vector<Chromosome *> retVal;
        for (int i = 0; i < in.size(); i++) {
            retVal.push_back(new Chromosome((*in[i])));
        }
        return retVal;
    }

    static std::string readFile(std::string fName) {
        std::ifstream ifs;
        ifs.open(fName, std::ifstream::in);
        std::string content;
        content.assign((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));
        ifs.close();
        return content;
    }

    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    static std::vector<int> toIntVec(std::vector<std::string>& tokens) {
        std::vector<int> retVal;
        std::string::size_type sz; // alias of size_t
        for (int i = 0; i < tokens.size(); i++) {
            int i_dec = std::stoi(tokens[i], &sz);
            retVal.push_back(i_dec);
        }
        return retVal;
    }

    static void readReferenceMonograms(float *out) {
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
            out[first[0] - 'a'] = (float) std::stod(second, &sz);
        }
    }

    static void readReferenceBigrams(float **out) {
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
            out[first[0] - 'a'][first[1] - 'a'] = (float) std::stod(second, &sz);
        }
    }

    static void readReferenceTrigrams(float ***out) {
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
            out[first[0] - 'a'][first[1] - 'a'][first[2] - 'a'] = (float) std::stod(second, &sz);
        }
    }

    //https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c
    static std::vector<std::vector<int>> comb(int N, int K) {
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
};
#endif // HELPERS_H_INCLUDED
