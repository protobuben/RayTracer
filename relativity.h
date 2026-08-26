#pragma once
#include "vec3.h"

inline vec3 aberrate(const vec3& d, const vec3& n, double beta) {
    // d - unit vec3
    const double a = dot(n, d);
    const double inv_gamma = std::sqrt(1.0-beta*beta);
    return ((a-beta)*n + inv_gamma*(d - a*n)) / (1.0 - a*beta);
}

inline double doppler_factor(const ray& r, const vec3& n, double beta) {
    const double a = dot(unit_vec3(r.direction), n);
    const double gamma = 1.0 / std::sqrt(1.0-beta*beta);
    return 1.0 / (gamma * (1.0 + a*beta));
}