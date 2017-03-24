#include "Cipher.h"

#include "Helpers.h"

void Cipher::loadCipherText(std::string fName)
{
    std::string fContent = Helpers::readFile(fName);
    std::vector<std::string> tokens = Helpers::split(fContent, ' ');
    cipherText = Helpers::toIntVec(tokens);
    plainText.resize(cipherText.size());
}

std::string Cipher::decrypt(const std::string& key)
{

    plainText.resize(cipherText.size());
    for (int i = 0; i < cipherText.size(); i++) {
        int idx = cipherText[i];
        plainText[i] = key[idx];
    }
    return plainText;
}
