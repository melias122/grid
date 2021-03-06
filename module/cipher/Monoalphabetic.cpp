#include "Monoalphabetic.h"

#include "utils/Common.h"

using namespace std;

Monoalphabetic *Monoalphabetic::fromFile(string path)
{
    return new Monoalphabetic(Helpers::readFile(path));
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
