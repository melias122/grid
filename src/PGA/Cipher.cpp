#include "Cipher.h"

#include "Helpers.h"

string Cipher::encrypt(const string& plainText, const string& key)
{
    string cipherText(plainText.size(), 0);
    for (int i = 0; i < plainText.size(); i++) {
        int idx = plainText[i] - 'a';
        cipherText[i] = key[idx];
    }
    return cipherText;
}

string Cipher::decrypt(const string& cipherText, const string& key)
{
    string plainText(cipherText.size(), 0);
    for (int i = 0; i < cipherText.size(); i++) {
        int idx = cipherText[i] - 'a';
        plainText[i] = key[idx];
    }
    return plainText;
}

string Monoalphabetic::encrypt(const string& plainText, const string& key)
{
    string cipherText(plainText.size(), 0);
    for (int i = 0; i < plainText.size(); i++) {
        int j = plainText[i] - 'a';
        cipherText[i] = key[j];
    }
    return cipherText;
}

string Monoalphabetic::decrypt(const string& cipherText, const string& key)
{
    return encrypt(cipherText, key);
}

string Monoalphabetic::createDecryptionKey(string encryptionKey)
{
    string key(encryptionKey.size(), 0);
    for (int i = 0; i < key.size(); i++) {
        key[encryptionKey[i] - 'a'] = i + 'a';
    }
    return key;
}
