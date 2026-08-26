#pragma once
#include "vec3.h"
#include <cmath>
#include <algorithm>

inline vec3 tonemap(vec3 c) {
    const double m = std::min({c.x, c.y, c.z});
    if (m < 0.0) c += vec3(-m, -m, -m);

    const double L = 0.2126*c.x + 0.7152*c.y + 0.0722*c.z;
    if (L > 0.0) c = c * ((L/(1.0+L)) / L);

    const double mx = std::max({c.x, c.y, c.z});
    if (mx > 1.0) c = c / mx;

    return c;
}

inline double apply_gamma(double v) {
    if (v <= 0.0031308) { 
        return v * 12.92;
    } else {
        return 1.055 * std::pow(v, 1.0/2.4) - 0.055;
    }
}

inline double x_hat(double lambda) {
    const double tosquare1 = (lambda-595.8)/33.33;
    const double tosquare2 = (lambda-446.8)/19.44;
    return 1.065*exp(-.5 * tosquare1*tosquare1) + 0.366*exp(-.5 * tosquare2*tosquare2);
} 
inline double y_hat(double lambda) {
    const double tosquare = std::log(lambda/556.3)/0.075;
    return 1.014*exp(-.5 * tosquare*tosquare);
} 
inline double z_hat(double lambda) {
    const double tosquare = std::log(lambda/449.8)/0.051;
    return 1.839*exp(-.5 * tosquare*tosquare);
} 

inline vec3 wavelength_to_xyz(double lambda) {
    return vec3(x_hat(lambda), y_hat(lambda), z_hat(lambda));
}

inline vec3 xyz_to_srgb(const vec3& xyz) {
    vec3 srgb_prime(
        dot(vec3( 3.2404542, -1.5371385, -0.4985314), xyz),
        dot(vec3(-0.9692660,  1.8760108,  0.0415560), xyz),
        dot(vec3( 0.0556434, -0.2040259,  1.0572252), xyz)
    );
    srgb_prime = tonemap(srgb_prime);
    return vec3(
        apply_gamma(srgb_prime.x),
        apply_gamma(srgb_prime.y),
        apply_gamma(srgb_prime.z)
    );
}
