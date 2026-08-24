#include <iostream>
#include <fstream>
#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "hittable.h"
#include <vector>
#include <memory>
#include "hittable_list.h"


void write_color(std::ostream& out, const vec3& pixel_color) {

    const int r = static_cast<int>(255.999*pixel_color.x);
    const int g = static_cast<int>(255.999*pixel_color.y);
    const int b = static_cast<int>(255.999*pixel_color.z);

    out << r << " " << g << " " << b << "\n";
}

int main() {
    std::ofstream out("image.ppm");
    const int horizontal = 800;
    const int vertical = 600;
    const vec3 light_direction = vec3(-1.0, -1.0, -.5);

    hittable_list world;
    world.add(std::make_shared<sphere>(vec3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(vec3(-.2,.3,-.9), 0.3, vec3(1.0, 1.0, 0.0)));
    world.add(std::make_shared<sphere>(vec3(.2,-.3,-.9), 0.3, vec3(1.0, 0.0, 1.0)));
    world.add(std::make_shared<sphere>(vec3(.4,-.2,-1), 0.4, vec3(0.0, 1.0, 1.0)));
    
    world.add(std::make_shared<plane>(vec3(2, -.6, 0.8), vec3(-.6,.3,-.6), .1, .2, vec3(1.0, 0.0, 0.0)));
    world.add(std::make_shared<plane>(vec3(-2, 3, 0.8), vec3(.5,-0.3,-.6), .1, .2, vec3(0.0, 1.0, 0.0)));
    world.add(std::make_shared<plane>(vec3(0.1, -.3, 0.8), vec3(0.4,-0.6,-.8), .6, .4, vec3(0.0, 0.0, 1.0)));

    world.add(std::make_shared<plane>(vec3(0, 1, 0), vec3(0, -1,-1), 3, 3));

    out << "P3\n" << horizontal << " " << vertical << "\n255\n";

    camera cam(horizontal, vertical, vec3(0.0, 0.0, .5));

    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {
            vec3 pixel_color;
            const ray r = cam.project(i, j);

            hit_record record;

            if (!world.hit(r, 0.001, 1e9, record)) { write_color(out, vec3()); continue; } 
             const ray shadow_ray(record.p, -light_direction);
            hit_record tmp;
            const double brightness = std::max(dot(-light_direction, record.normal), 0.0);
            const bool in_shadow = world.hit(shadow_ray, 0.001, 1e9, tmp);

            if (in_shadow) { write_color(out, record.color * 0.1); continue; }

            pixel_color = record.color * (.1 + .9*brightness);

            write_color(out, pixel_color);

        }
    }

    return 0;
}