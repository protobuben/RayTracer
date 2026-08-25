#pragma once
#include <ostream>
#include <algorithm>
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "hittable.h"
#include "constants.h"


inline void write_color(std::ostream& out, const vec3& pixel_color) {

    const int r = static_cast<int>(256*clamp0_0999(pixel_color.x));
    const int g = static_cast<int>(256*clamp0_0999(pixel_color.y));
    const int b = static_cast<int>(256*clamp0_0999(pixel_color.z));

    out << r << " " << g << " " << b << "\n";
}

inline vec3 ray_color(const ray& r, const hittable& world, const vec3& light_dir) {
    hit_record record;

    if (!world.hit(r, eps, infinity, record)) { return vec3(); } 

    const ray shadow_ray(record.p, -light_dir);
    hit_record tmp;
    const double brightness = std::max(dot(-light_dir, record.normal), 0.0);
    const bool in_shadow = world.hit(shadow_ray, eps, infinity, tmp);

    if (in_shadow) { return record.color * 0.1; }

    return record.color * (.1 + .9*brightness);
}

inline void render (std::ostream& out, const camera& cam, const hittable& world, const vec3& light_dir, const double samples = 8) {
    const int horizontal = cam.resX;
    const int vertical = cam.resY;
    out << "P3\n" << horizontal << " " << vertical << "\n255\n";

    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {
            vec3 pixel_color;
            for (int s = 0; s < samples; s++){
                pixel_color += ray_color(cam.project(i, j, (random_double()-.5), (random_double()-.5)), world, light_dir);
            }

            write_color(out, (pixel_color/samples));
        }
        std::cerr << "\rprogress: " << j << '/' << vertical << std::flush;
    }
}