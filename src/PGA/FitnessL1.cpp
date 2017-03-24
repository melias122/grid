#include "FitnessL1.h"
#include "Chromosome.h"
#include "Helpers.h"
#include "math.h"
#include <string.h>

FitnessL1::FitnessL1(int n) { init(n); }

FitnessL1::FitnessL1(const FitnessL1& other) { init(other.n); }

FitnessL1::~FitnessL1()
{
    if (refMono) {
        delete refMono;
    }
    if (refBi) {
        delete[] refBi;
    }

    if (refTri) {
        delete[] refTri;
    }
}

void FitnessL1::init(int n)
{
    n = n;
    switch (n) {
    case 1: {
        refMono = new double[26]();
        Helpers::readReferenceMonograms(refMono);
    } break;
    case 2: {
        refBi = new double*[26];
        for (int i = 0; i < 26; i++) {
            refBi[i] = new double[26]();
            memset(refBi[i], 0, 26);
        }
        Helpers::readReferenceBigrams(refBi);

    } break;
    case 3: {
        refTri = new double**[26];
        for (int i = 0; i < 26; i++) {
            refTri[i] = new double*[26];
            for (int j = 0; j < 26; j++) {
                refTri[i][j] = new double[26]();
            }
        }
        Helpers::readReferenceTrigrams(refTri);

    } break;
    };
}

double FitnessL1::evaluate(std::string& in)
{
    //	std::cout << "FitnessL1::evaluate" << std::endl;
    double score = 0;
    switch (n) {
    case 1: {
        score = L1DistanceMonograms(in);
    } break;
    case 2: {
        score = L1DistanceBigrams(in);
    } break;
    case 3: {
        score = L1DistanceTrigrams(in);
    } break;
    }
    return -score;
}

double FitnessL1::L1DistanceMonograms(std::string& in)
{
    double* m = new double[26]();

    for (int i = 0; i < in.length(); i++) {
        char a = in[i];
        m[a - 'a'] += 1.0f;
    }
    double sum = 0;
    double div = in.length();
    for (int i = 0; i < 26; i++) {
        double nv = refMono[i] - (m[i] / div);
        sum += fabs(nv);
    }

    delete m;
    return sum;
}

double FitnessL1::L1DistanceBigrams(std::string& in)
{
    double m[26][26];

    std::cout << "x" << std::endl;
    for (int i = 0; i < in.length() - 1; i++) {
        std::cout << in[i] << " " << in[i + 1] << std::endl;
        //		m[in[i] - 'a'][in[i + 1] - 'a'] += 1.0f;
    }

    double sum = 0;
    double div = in.length() - 1;
    std::cout << "x" << std::endl;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            double nv = refBi[i][j] - (m[i][j] / div);
            sum += fabs(nv);
        }
    }

    return sum;
}

double FitnessL1::L1DistanceTrigrams(std::string& in)
{
    double*** m = new double**[26];
    for (int i = 0; i < 26; i++) {
        m[i] = new double*[26];
        for (int j = 0; j < 26; j++) {
            m[i][j] = new double[26]();
        }
    }
    for (int i = 0; i < in.length() - 2; i++) {
        char a = in[i];
        char b = in[i + 1];
        char c = in[i + 2];
        m[a - 'a'][b - 'a'][c - 'a'] += 1.0f;
    }
    double sum = 0;
    double div = in.length() - 2;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 0; k < 26; k++) {
                double nv = refTri[i][j][k] - (m[i][j][k] / div);
                sum += fabs(nv);
            }
        }
    }
    delete[] m;
    return sum;
}
