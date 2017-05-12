#include "L1.h"

#include "utils/Common.h"

#include <cmath>
#include <sstream>
#include <tuple>

using namespace std;

static vector<tuple<string, double>> parseCsv(string path)
{
    string first, second, line;
    stringstream ss(Helpers::readFile(path));
    vector<tuple<string, double>> values;

    while (getline(ss, line, '\n')) {
        stringstream ls(line);
        getline(ls, first, ',');
        getline(ls, second, ',');
        values.push_back(make_tuple(first, stod(second)));
    }
    return values;
}

L1DistanceMonograms::L1DistanceMonograms(
    const vector<double> &referenceMonograms)
    : m_monograms{ referenceMonograms }
{
}

L1DistanceMonograms *L1DistanceMonograms::fromFile(string path)
{
    vector<double> monograms(26, 0);

    for (const tuple<string, double> &t : parseCsv(path)) {
        string s = get<0>(t);
        monograms[s[0] - 'a'] = get<1>(t);
    }

    return new L1DistanceMonograms(monograms);
}

double L1DistanceMonograms::evaluate(const string &pt)
{
    double m[26] = { 0 };
    double sum = 0, div = pt.size();

    for (int i = 0; i < pt.size(); i++) {
        m[pt[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        sum += fabs(m_monograms[i] - (m[i] / div));
    }

    return -sum;
}

L1DistanceBigrams::L1DistanceBigrams(const vector<vector<double>> &referenceBigrams)
    : m_bigrams{ referenceBigrams }
{
}

L1DistanceBigrams *L1DistanceBigrams::fromFile(string path)
{
    vector<vector<double>> bigrams(26);
    for (vector<double> &v : bigrams) {
        v.resize(26, .0);
    }

    for (const tuple<string, double> &t : parseCsv(path)) {
        string s = get<0>(t);
        bigrams[s[0] - 'a'][s[1] - 'a'] = get<1>(t);
    }

    return new L1DistanceBigrams(bigrams);
}

void L1DistanceBigrams::setCache(LRU::Cache<string, double> *cache)
{
    m_cache = cache;
}

double L1DistanceBigrams::evaluate(const string &pt)
{
    if (m_cache && m_cache->contains(pt)) {
        return m_cache->lookup(pt);
    }

    double m[26][26] = { 0 };
    double sum = 0, div = pt.size() - 1;

    for (size_t i = 0; i < pt.size() - 1; i++) {
        m[pt[i] - 'a'][pt[i + 1] - 'a'] += 1.0;
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            sum += fabs(m_bigrams[i][j] - (m[i][j] / div));
        }
    }
    sum = -sum;
    if (m_cache) {
        m_cache->emplace(pt, sum);
    }

    return sum;
}

L1DistanceTrigrams::L1DistanceTrigrams(const vector<vector<vector<double>>> &referenceTrigrams)
    : m_trigrams{ referenceTrigrams }
{
}

L1DistanceTrigrams *L1DistanceTrigrams::fromFile(string path)
{
    vector<vector<vector<double>>> trigrams(26);
    for (vector<vector<double>> &vv : trigrams) {
        vv.resize(26);
        for (vector<double> &v : vv) {
            v.resize(26, .0);
        }
    }

    for (const tuple<string, double> &t : parseCsv(path)) {
        string s = get<string>(t);
        trigrams[s[0] - 'a'][s[1] - 'a'][s[2] - 'a'] = get<double>(t);
    }

    return new L1DistanceTrigrams(trigrams);
}

double L1DistanceTrigrams::evaluate(const string &pt)
{
    double m[26][26][26] = { 0 };
    double sum = 0, div = pt.size() - 2;

    for (size_t i = 0; i < pt.size() - 2; i++) {
        m[pt[i] - 'a'][pt[i + 1] - 'a'][pt[i + 2] - 'a'] += 1.0;
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
