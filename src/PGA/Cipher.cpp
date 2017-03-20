#include "Cipher.h"

#include "Helpers.h"

Cipher::Cipher() {

}

Cipher::Cipher(const Cipher& other) {
    this->cipherText = other.cipherText;
    this->plainText = other.plainText;
}

void Cipher::loadCipherText(std::string fName) {
    std::string fContent = Helpers::readFile(fName);
    std::vector<std::string> tokens = Helpers::split(fContent, ' ');
    this->cipherText = Helpers::toIntVec(tokens);


}

std::string Cipher::decrypt(std::vector<char>& key) {
//    std::cout << "decrypt :" << "\n ";
//    std::cout << "key :" << "\n ";
//
//    for (int i = 0; i < key.size(); i++) {
//        std::cout << key[i] << "";
//    }
//    std::cout << "\n";
//    std::cout << "result :" << "\n ";


    std::string pt;
    pt.reserve(this->cipherText.size());
    for (int i = 0; i < this->cipherText.size(); i++) {
        int idx = this->cipherText[i];
        pt += key[idx];
    }
    this->plainText = std::string(pt);

//    std::cout << "\n ";//pt << 
//    std::cout << "end" << "\n ";
    return pt;
}


