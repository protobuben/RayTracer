#pragma once
#include "vec3.h"

inline vec3 aberrate(const vec3& d, const vec3& n, double beta) {
    // d - unit vec3
    const double a = dot(n, d);
    const double inv_gamma = std::sqrt(1.0-beta*beta);
    return ((a-beta)*n + inv_gamma*(d - a*n)) / (1.0 - a*beta);
}

inline double doppler_factor(const vec3& d, const vec3& n, double beta) {
    const double a = dot(unit_vec3(d), n);
    const double gamma = 1.0 / std::sqrt(1.0-beta*beta);
    return (gamma * (1.0 + a*beta));
}

inline double beaming_factor(double doppler) {
    return doppler*doppler*doppler*doppler;
}

// Schwarzschild
inline double gravitational_wavelength_shift(double rs, double r_out, double r_in) {
    return std::sqrt((1 - rs/r_in)/(1 - rs/r_out));
}

inline double doppler_from_source(const vec3& d, const vec3& beta_src) {
    const double beta = beta_src.length();
    if (beta <= 1e-12) return 1.0;
    return doppler_factor(d, -beta_src/beta, beta);
}