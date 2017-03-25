#ifndef CIPHER_H
#define CIPHER_H

#include "Chromosome.h"

using namespace std;

class Cipher
{
public:
    virtual void decrypt(const string &key, string &plaintext) = 0;
};

class Monoalphabetic : public Cipher
{
public:
    Monoalphabetic(const string &ciphertext)
        : m_ciphertext{ ciphertext }
    {
    }
    static Monoalphabetic *fromFile(string path);
    void decrypt(const string &key, string &plaintext) override;

private:
    string m_ciphertext;
};

#endif // CIPHER_H
