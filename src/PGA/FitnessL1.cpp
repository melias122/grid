#include "FitnessL1.h"
#include "Chromosome.h"
#include "Helpers.h"
#include "math.h"

#include <string>
#include <tuple>

using namespace std;

static vector<tuple<string, double> > parseCsv(string path)
{
    string s, first, second, line;
    if (!Helpers::readFile(s, path)) {
        return {};
    }

    stringstream ss(s);
    vector<tuple<string, double> > values;
    while (getline(ss, line, '\n')) {
        stringstream ls(line);
        getline(ls, first, ',');
        getline(ls, second, ',');
        values.push_back(make_tuple(first, stod(second)));
    }
    return values;
}

L1DistanceMonograms::L1DistanceMonograms(const vector<double>& referenceMonograms)
    : m_monograms{ referenceMonograms }
{
}

L1DistanceMonograms* L1DistanceMonograms::fromFile(string path)
{
    auto values = parseCsv(path);

    vector<double> monograms(26, 0);
    for (const tuple<string, double>& t : values) {
        string s = get<0>(t);
        monograms[s[0] - 'a'] = get<1>(t);
    }

    return new L1DistanceMonograms(monograms);
}

double L1DistanceMonograms::evaluate(const string& in)
{
    double m[26] = { 0 };
    double sum = 0, div = in.length();

    for (int i = 0; i < in.length(); i++) {
        char a = in[i];
        m[a - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        sum += fabs(m_monograms[i] - (m[i] / div));
    }

    return -sum;
}

L1DistanceBigrams::L1DistanceBigrams(const vector<vector<double> >& referenceBigrams)
    : m_bigrams{ referenceBigrams }
{
}

L1DistanceBigrams* L1DistanceBigrams::fromFile(string path)
{
    auto values = parseCsv(path);

    vector<vector<double> > bigrams(26);
    for (vector<double>& v : bigrams) {
        v.resize(26, .0);
    }

    for (const tuple<string, double>& t : values) {
        string s = get<0>(t);
        bigrams[s[0] - 'a'][s[1] - 'a'] = get<1>(t);
    }

    return new L1DistanceBigrams(bigrams);
}

double L1DistanceBigrams::evaluate(const string& in)
{
    double m[26][26] = { 0 };
    double sum = 0, div = in.length() - 1;

    for (size_t i = 0; i < in.length() - 1; i++) {
        m[in[i] - 'a'][in[i + 1] - 'a'] += 1.0;
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            sum += fabs(m_bigrams[i][j] - (m[i][j] / div));
        }
    }

    return -sum;
}

L1DistanceTrigrams::L1DistanceTrigrams(const vector<vector<vector<double> > >& referenceTrigrams)
{
}

L1DistanceTrigrams* L1DistanceTrigrams::fromFile(std::string path)
{
}

double L1DistanceTrigrams::evaluate(const std::string& in)
{
    double m[26][26][26] = { 0 };
    double sum = 0, div = in.length() - 2;

    for (size_t i = 0; i < in.length() - 2; i++) {
        char a = in[i];
        char b = in[i + 1];
        char c = in[i + 2];
        m[a - 'a'][b - 'a'][c - 'a'] += 1.0f;
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 0; k < 26; k++) {
                sum += fabs(m_trigrams[i][j][k] - (m[i][j][k] / div));
            }
        }
    }

    return -sum;
}
