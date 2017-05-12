#ifndef _Cipher_h
#define _Cipher_h

#include <string>

class Cipher
{
public:
    ~Cipher() {}
  virtual void decrypt(const std::string &key, std::string &plaintext) = 0;
};

#endif
