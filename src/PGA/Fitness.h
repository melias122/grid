#ifndef FITNESS_H
#define FITNESS_H

#include <string>

class Fitness {
public:

    virtual float evaluate(std::string& in);
};

#endif // FITNESS_H
