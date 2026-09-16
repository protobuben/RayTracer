#pragma once
#include <ostream>
#include <algorithm>
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "hittable.h"
#include "constants.h"
#include "color.h"
#include "blackhole.h"
#include "geodesic.h"
#include "schwarzschild.h"

inline void write_color(std::ostream& out, const vec3& pixel_color) {

    const int r = static_cast<int>(256*clamp0_0999(pixel_color.x));
    const int g = static_cast<int>(256*clamp0_0999(pixel_color.y));
    const int b = static_cast<int>(256*clamp0_0999(pixel_color.z));

    out << r << " " << g << " " << b << "\n";
}


enum class march_result { hit, escaped, horizon };

struct march_out {
    march_result result;
    hit_record record;
    vec3 dir;
};


inline march_out march(const vec3& origin, const vec3& dir, const hittable& world, const blackhole& bh) {
    geo_frame fr;
    gstate s = from_camera_to_gstate(origin, dir, bh.center, bh.rs, fr);
    march_out out;

    vec3 a = to_cartesian(s, bh.center, fr);
    for (int i = 0; i < bh.max_steps; i++) {
        const double step = bh.h * std::max(1.0, s.x[1] / (4.0 * bh.rs));
        rk4_step(s, bh.rs, step);
        const vec3 b = to_cartesian(s, bh.center, fr);
 
        if (world.hit(ray(a, b-a), 0.0, 1.0, out.record)) {
            out.result = march_result::hit;
            return out;
        }
        if (s.x[1] < 1.05 * bh.rs) { out.result = march_result::horizon; return out; }
        if (s.x[1] > bh.escape_r) {
            out.result = march_result::escaped;
            out.dir = b-a;
            return out;
        }
        a = b;
    }
    out.result = march_result::horizon;
    return out;
}


inline uint32_t hash32(uint32_t x) {
    x ^= x >> 16; x *= 0x7feb352d; x ^= x >> 15; x *= 0x846ca68b; x ^= x >> 16; return x;
}

inline bool star_background(const vec3& dir, double& lambda, double& gain) {
    const int N = 220; const double density = .03;

    const vec3 d = unit_vec3(dir);
    const double ax = std::fabs(d.x), ay = std::fabs(d.y), az = std::fabs(d.z);
    uint32_t f; double u, v;

    if (ax >= ay && ax >= az) { f = d.x>0?0:1; u = d.y/ax; v = d.z/ax; }
    else if (ay >= az)        { f = d.y>0?2:3; u = d.z/ay; v = d.x/ay; }
    else                      { f = d.z>0?4:5; u = d.x/az; v = d.y/az; }
    
    const uint32_t iu = uint32_t((u*0.5+0.5)*N), iv = uint32_t((v*0.5+0.5)*N);
    const uint32_t h = hash32(((f*N + iu)*N + iv) + 0x9e3779b9);
    const double w = std::pow(1.0 + u*u + v*v, -1.5);

    if (h > uint32_t(density * w * 4294967296.0)) return false;
    gain   = std::pow(hash32(h)*2.3283064e-10, 2.0);
    lambda = 460.0 + 190.0 * hash32(h+1)*2.3283064e-10;
    return true;
}

inline vec3 ray_color(const ray& r, const hittable& world, const vec3& light_dir, const vec3& cam_dir, double beta, const blackhole& bh) {
    const double D = doppler_factor(r, cam_dir, beta);
    double brightness = beaming_factor(D);
    
    vec3 color = vec3();
    bool in_shadow = false;

    const march_out m = march(r.origin, r.direction, world, bh);

    if (m.result == march_result::horizon) return vec3();

    if (m.result == march_result::hit) { 
        if (m.record.emissive) {
            color = xyz_to_srgb(wavelength_to_xyz(m.record.wavelength / D));
            // brightness stays as beaming_factor(D) alone - no dot product, no shadow ray
        } else {
            brightness *= std::max(dot(-light_dir, m.record.normal), 0.0);
            const ray shadow_ray(m.record.p, -light_dir);
            hit_record tmp;
            in_shadow = world.hit(shadow_ray, eps, infinity, tmp);
            color = xyz_to_srgb(wavelength_to_xyz(m.record.wavelength / D));
        }
    } else {
        double lambda, gain;
        if (!star_background(r.direction, lambda, gain)) return vec3();
        color = xyz_to_srgb(wavelength_to_xyz(lambda / D));
        brightness *= gain;
    }

    if (in_shadow) { return color * 0.1; }
    return color * (brightness);
}

inline void render (std::ostream& out, const camera& cam, const hittable& world, const vec3& light_dir, const blackhole& bh, const double samples = 8) {
    const int horizontal = cam.resX;
    const int vertical = cam.resY;
    out << "P3\n" << horizontal << " " << vertical << "\n255\n";

    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {
            vec3 pixel_color;
            for (int s = 0; s < samples; s++){
                pixel_color += ray_color(cam.project(i, j, (random_double()-.5), (random_double()-.5)), world, light_dir, cam.velocity_dir, cam.beta, bh);
            }

            write_color(out, (pixel_color/samples));
        }
        std::cerr << "\rprogress: " << j << '/' << vertical << std::flush;
    }
}