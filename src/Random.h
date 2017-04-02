#ifndef GRID_RANDOM_H
#define GRID_RANDOM_H

#include <limits>
#include <random>

// note: this header is not Thread-safe

constexpr uint64_t uint64_min = std::numeric_limits<uint64_t>::min();
constexpr uint64_t uint64_max = std::numeric_limits<uint64_t>::max();

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

    uint64_t Uint64(uint64_t min = uint64_min, uint64_t max = uint64_max)
    {
        std::uniform_int_distribution<uint64_t> dist(min, max);
        return dist(_mt);
    }

    double Double(double min = 0, double max = double_max)
    {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(_mt);
    }

private:
    // random_device is used to seed mersenne twister random number generator
    std::random_device _rd;
    std::mt19937_64 _mt;
};

static RNG Random;

#endif
