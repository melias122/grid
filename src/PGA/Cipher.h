#ifndef CIPHER_H
#define CIPHER_H

#include <string>
#include <vector>

#include "Chromosome.h"

using namespace std;

class Cipher {
public:
    virtual string encrypt(const string& plainText, const string& key) = 0;
    virtual string decrypt(const string& cipherText, const string& key) = 0;
};

class Monoalphabetic : public Cipher {
public:
    string encrypt(const string& plainText, const string& key) override;
    string decrypt(const string& cipherText, const string& key) override;

    // pomocna funkcia
    static string createDecryptionKey(string encryptionKey);
};

#endif // CIPHER_H
