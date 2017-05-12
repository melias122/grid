#ifndef GRID_RANDOM_H
#define GRID_RANDOM_H

#include <algorithm>
#include <limits>
#include <random>

// note: this header is not Thread-safe

constexpr int int_min = std::numeric_limits<int>::min();
constexpr int int_max = std::numeric_limits<int>::max();

constexpr double double_min = std::numeric_limits<double>::min();
constexpr double double_max = std::numeric_limits<double>::max();

class RNG
{
public:
    RNG()
        : _rd{}
        , _mt{ _rd() }
    {
    }

    // generates int from range <min, max>
    int Int(int min = 0, int max = int_max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(_mt);
    }

    // Generates random double from range <min, max>.
    // By default min is set to 0
    double Double(double min = 0, double max = double_max)
    {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(_mt);
    }

    template <class Iterator>
    void Shuffle(Iterator first, Iterator last)
    {
        std::shuffle(first, last, _mt);
    }

    template <class Vector>
    auto &Item(const Vector &v)
    {
        int i = Int(0, v.size() - 1);
        return v[i];
    }

private:
    // random_device is used to seed mersenne twister random number generator
    std::random_device _rd;
    std::mt19937_64 _mt;
};

static RNG Random;

#endif
