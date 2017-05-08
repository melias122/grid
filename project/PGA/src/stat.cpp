#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct stat {
    using match_counter = unordered_map<int, int>;
    using textsize_match = unordered_map<int, match_counter>;
    using schema_stat = unordered_map<string, textsize_match>;
    using popsize_schema = unordered_map<int, schema_stat>;

    unordered_map<int, popsize_schema> itterations;

    void add(int textsize, int match, int _itterations, int popsize, string schema)
    {
        itterations[_itterations][popsize][schema][textsize][match]++;
    }

    double calc(const match_counter &cnt, int textsize)
    {
        double a = 0, b = 0;
        for (const auto &c : cnt) {
            double match = (double)c.first;
            double count = (double)c.second;

            double x = (match / textsize) * count;
            a += x;
            b += count;
        }
        return a / b;
    }

    auto calc(const textsize_match &tsm)
    {
        vector<pair<int, double>> points;
        for (const auto &t : tsm) {
            double mean = calc(t.second, t.first);
            points.emplace_back(t.first, mean);
        }
        sort(points.begin(), points.end(), [](const auto &rhs, const auto &lhs) { return rhs.first < lhs.first; });
        return points;
    }
};

// text size; match; itterations; initial population; schema ID
// 50       ; 41   ; 10000      ; 10                ; J
int main()
{
    int textsize, match, itterations, popsize;
    string schemaId;
    stat s;

    //    string line;
    while (cin >> textsize >> match >> itterations >> popsize >> schemaId) {
        s.add(textsize, match, itterations, popsize, schemaId);
    }

    for (const auto &itt : s.itterations) {
        for (const auto &pop : itt.second) {
            for (const auto &sch : pop.second) {

                string filename(to_string(itt.first) + "_" + to_string(pop.first) + "_" + sch.first);
                cout << "writing to " << filename << endl;
                ofstream file(filename);
                if (!file.is_open()) {
                    cerr << "can't open file " << filename;
                    return 1;
                }

                for (const auto &p : s.calc(sch.second)) {
                    file << p.first << "\t" << p.second << endl;
                }
                file.flush();
                file.close();
            }
        }
    }

    return 0;
}
