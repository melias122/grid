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
    float evaluate(std::string& in);

protected:
    int n;
    float* refMono;
    float** refBi;
    float*** refTri;

private:

    float L1DistanceMonograms(std::string& in);
    float L1DistanceBigrams(std::string& in);
    float L1DistanceTrigrams(std::string& in);


};

#endif // FITNESS_L1_H
