#ifndef CIPHER_H
#define CIPHER_H

#include "Chromosome.h"

#include <string>

class Cipher
{
public:
    ~Cipher() {}
    virtual void decrypt(const Genes &key, std::string &plaintext) = 0;
};

class Monoalphabetic : public Cipher
{
public:
    Monoalphabetic(const std::string &ciphertext)
        : m_ciphertext{ ciphertext }
    {
    }
    static Monoalphabetic *fromFile(std::string path);
    void decrypt(const Genes &key, std::string &plaintext) override;

private:
    std::string m_ciphertext;
};

#endif // CIPHER_H
