#ifndef UTILS_H
#define UTILS_H

#include <random>

class CyclicCounter {
    private:
        const int initial_value;
        int value;

    public:
        CyclicCounter(int initial_value = 5);

        bool is_zero() const;
        CyclicCounter operator--(int);
};

class RandomGenerator {
    private:
        std::random_device device;
        std::minstd_rand generator;
        std::uniform_int_distribution<int> distribution;

    public:
        RandomGenerator(int, int);

        int operator()();
};

#endif
