#ifndef FITNESS_L1_H
#define FITNESS_L1_H

//#include <vector>
//#include <string>
#include "Fitness.h"
//

class FitnessL1 : public Fitness {
public:
    FitnessL1(int n);
    FitnessL1(const FitnessL1& other);
    ~FitnessL1();

    void init(int n);
    double evaluate(std::string& in);

protected:
    int n;
    double* refMono;
    double** refBi;
    double*** refTri;

private:
    double L1DistanceMonograms(std::string& in);
    double L1DistanceBigrams(std::string& in);
    double L1DistanceTrigrams(std::string& in);
};

#endif // FITNESS_L1_H
