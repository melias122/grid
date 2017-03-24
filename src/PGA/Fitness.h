#ifndef FITNESS_H
#define FITNESS_H

#include <string>

class Fitness {
public:
    ~Fitness() {}
    virtual double evaluate(std::string& in) = 0;
};

#endif // FITNESS_H