#ifndef CIPHER_H
#define CIPHER_H

#include <string>
#include <vector>

#include "Chromosome.h"

class Cipher {
public:
    void loadCipherText(std::string fName);
    //    std::string encrypt(std::vector<char>& key);
    std::string decrypt(const std::__cxx11::string& key);

    std::vector<int> getCipherText() { return cipherText; }

    std::string getPlainText() { return plainText; }

protected:
    std::vector<int> cipherText;
    std::string plainText;
};

#endif // CIPHER_H
