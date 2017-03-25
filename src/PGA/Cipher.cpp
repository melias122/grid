#include "Cipher.h"

#include "Helpers.h"

Monoalphabetic *Monoalphabetic::fromFile(string path)
{
    string ciphertext;
    if (!Helpers::readFile(ciphertext, path)) {
        return nullptr;
    }
    return new Monoalphabetic(ciphertext);
}

void Monoalphabetic::decrypt(const string &key, string &plaintext)
{
    if (plaintext.size() != m_ciphertext.size()) {
        plaintext.resize(m_ciphertext.size(), 0);
    }

    for (int i = 0; i < m_ciphertext.size(); i++) {
        int j = m_ciphertext[i] - 'a';
        plaintext[i] = key[j];
    }
}
