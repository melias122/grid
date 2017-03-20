#include "FitnessL1.h"
#include "Chromosome.h"
#include "Helpers.h"
#include "math.h"

FitnessL1::FitnessL1(int n) {
    this->init(n);
}

FitnessL1::FitnessL1(const FitnessL1& other) {
    this->init(other.n);
}

FitnessL1::~FitnessL1() {
    if (refMono) {
        delete refMono;
    }
    if (refBi) {
        delete [] refBi;
    }

    if (refTri) {
        delete [] refTri;
    }

}

void FitnessL1::init(int n) {
    this->n = n;
    switch (this->n) {
        case 1:
        {
            this->refMono = new float[26]();
            Helpers::readReferenceMonograms(this->refMono);
        }
            break;
        case 2:
        {
            this->refBi = new float*[26];
            for (int i = 0; i < 26; i++) {
                this->refBi[i] = new float[26]();
            }
            Helpers::readReferenceBigrams(this->refBi);

        }
            break;
        case 3:
        {
            this->refTri = new float**[26];
            for (int i = 0; i < 26; i++) {
                this->refTri[i] = new float*[26];
                for (int j = 0; j < 26; j++) {
                    this->refTri[i][j] = new float[26]();
                }
            }
            Helpers::readReferenceTrigrams(this->refTri);

        }
            break;
    };

}

float FitnessL1::evaluate(std::string& in) {
    float score = 0;
    switch (this->n) {
        case 1:
        {
            score = this->L1DistanceMonograms(in);
        }
            break;
        case 2:
        {
            score = this->L1DistanceBigrams(in);
        }
            break;
        case 3:
        {
            score = this->L1DistanceTrigrams(in);
        }
            break;
    }
    return -score;
}

float FitnessL1::L1DistanceMonograms(std::string& in) {
    float* m = new float[26]();

    for (int i = 0; i < in.length(); i++) {
        char a = in[i];
        m[a - 'a']+= 1.0f;
    }
    float sum = 0;
    float div = in.length();
    for (int i = 0; i < 26; i++) {
        float nv = refMono[i] - (m[i] / div);
        sum += fabs(nv);
    }

    delete m;
    return sum;
}

float FitnessL1::L1DistanceBigrams(std::string& in) {
    float **m = new float*[26];
    for (int i = 0; i < 26; i++) {
        m[i] = new float[26]();
    }

    for (int i = 0; i < in.length() - 1; i++) {
        char a = in[i];
        char b = in[i + 1];
        m[a - 'a'][b - 'a']+= 1.0f;
    }
    float sum = 0;
    float div = in.length() - 1;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
//            std::cout << refBi[i][j] << "," << m[i][j] << "," << (m[i][j] / div) << " = ";
            float nv = refBi[i][j] - (m[i][j] / div);
//            std::cout << nv << "\n";
            sum += fabs(nv);
        }
    }
//     std::cout << sum << "\n";
    delete [] m;
    return sum;
}

float FitnessL1::L1DistanceTrigrams(std::string& in) {
    float ***m = new float**[26];
    for (int i = 0; i < 26; i++) {
        m[i] = new float*[26];
        for (int j = 0; j < 26; j++) {
            m[i][j] = new float[26]();
        }
    }
    for (int i = 0; i < in.length() - 2; i++) {
        char a = in[i];
        char b = in[i + 1];
        char c = in[i + 2];
        m[a - 'a'][b - 'a'][c - 'a']+= 1.0f;
    }
    float sum = 0;
    float div = in.length() - 2;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 0; k < 26; k++) {
                float nv = refTri[i][j][k] - (m[i][j][k] / div);
                sum += fabs(nv);
            }
        }
    }
    delete [] m;
    return sum;
}
