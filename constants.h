#pragma once
#include <limits>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double eps = 0.001;

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double clamp0_0999(double x) { return std::min(std::max(x, 0.0), 0.999); }