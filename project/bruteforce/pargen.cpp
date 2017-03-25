#include "app.h"

#include <iostream>
#include <set>
#include <string>

using namespace std;

class Password : public Bruteforcer
{
public:
    Password(int max)
        : m_max{ max }
    {
    }

    void run(int procId, int nproc) override
    {
        string chars(m_max, 0);
        chars[0] = 'a' + procId;
        generate(1, m_max, chars);
    }

    void print()
    {
        for (const auto &r : m_results) {
            cout << r << "\n";
        }
    }

private:
    void generate(int level, int maxLevel, string &pwd)
    {
        if (level == maxLevel) {
            m_results.insert(string(pwd));
        } else {
            for (int i = 0; i < 26; i++) {
                pwd[level] = (char)(i + 'a');
                generate(level + 1, maxLevel, pwd);
            }
        }
    }

    int m_max;
    set<string> m_results;
};

int main(int argc, char **argv)
{
    int i;
    try {
        i = stoi(argv[1]);
    } catch (...) {
        cerr << argv[0] << " <n>\n";
        return EXIT_FAILURE;
    }

    Password pass(i);
    Runner::run(&pass);
    //	pass.print();
    return EXIT_SUCCESS;
}
