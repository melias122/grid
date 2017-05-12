#ifndef Monoalphabetic_h
#define Monoalphabetic_h

#include "Cipher.h"

class Monoalphabetic : public Cipher
{
public:
    Monoalphabetic(const std::string &ciphertext)
        : m_ciphertext{ ciphertext }
    {
    }
    static Monoalphabetic *fromFile(std::string path);
    void decrypt(const std::string &key, std::string &plaintext) override;

private:
    std::string m_ciphertext;
};

#endif
