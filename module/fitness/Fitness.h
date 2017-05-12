#ifndef FITNESS_H
#define FITNESS_H

#include <string>

class Fitness
{
public:
    ~Fitness() {}
    virtual double evaluate(const std::string &plaintext) = 0;
};

#endif
