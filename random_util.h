#ifndef RANDOM_UTIL_H
#define RANDOM_UTIL_H

#include <random>

namespace random_util {
    extern std::random_device rd;
    extern std::mt19937 gen;

    // Generate a random integer between min and max (inclusive)
    inline int randInt(int min, int max) {
        std::uniform_int_distribution<> distrib(min, max);
        return distrib(gen);
    }

    // Define the static variables in random_util.cpp
    inline void init() {
        gen.seed(rd());
    }
}

#endif
