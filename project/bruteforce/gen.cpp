#include <iostream>
#include <set>
#include <string>

using namespace std;

void allPasswords(int level, int maxLevel, string &pwd, set<string> &results)
{
    if (level == maxLevel) {
        results.insert(string(pwd));
    } else {
        for (int i = 0; i < 26; i++) {
            pwd[level] = (char)(i + 'a');
            allPasswords(level + 1, maxLevel, pwd, results);
        }
    }
}

void print(const set<string> &s)
{
    for (const auto &r : s) {
        cout << r << "\n";
    }
}

int main(int argc, char **argv)
{

    int i;
    try {
        i = stoi(argv[1]);
    } catch (...) {
        cerr << argv[0] << " <n>\n";
        return EXIT_FAILURE;
    }

    string chars(i, 0);
    set<string> results;

    allPasswords(0, i, chars, results);
    //	print(results);
    return 0;
}
