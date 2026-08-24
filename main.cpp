#include <iostream>
#include <fstream>
#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "camera.h"


void write_color(std::ostream& out, const vec3& pixel_color) {

    const int r = static_cast<int>(255.999*pixel_color.x);
    const int g = static_cast<int>(255.999*pixel_color.y);
    const int b = static_cast<int>(255.999*pixel_color.z);

    out << r << " " << g << " " << b << "\n";
}


double hit_sphere(const vec3& center, double radius, const ray& r) {
    const vec3 distance = r.origin - center;
    const double a = r.direction.dot_self();
    const double b = 2.0 * dot(r.direction, distance);
    const double c = distance.dot_self() - radius*radius;
    const double discr = b*b-4*a*c;
    return (-b - std::sqrt(discr))/(2*a);
}


int main() {
    std::ofstream out("image.ppm");
    const int horizontal = 320;
    const int vertical = 240;
    const vec3 light_direction = vec3(-1.0, -1.0, -.5);


    out << "P3\n" << horizontal << " " << vertical << "\n255\n";

    camera cam(horizontal, vertical);

    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {
            vec3 pixel_color;
            const ray r = cam.project(i, j);

            const vec3 sphere_center = vec3(0,0,-1);
            const double t = hit_sphere(sphere_center, .5, r);

            if (t > 0) {
                const vec3 sphere_point = r.at(t);
                const vec3 norm = unit_vec3(sphere_point-sphere_center);
                const double brightness = std::max(dot(-light_direction, norm), 0.0);
                pixel_color = vec3(1.0, 1.0, 1.0) * (.1 + .9*brightness);

            } else {
                pixel_color = vec3(0.0, 0.0, 0.0);    
            }
            
            write_color(out, pixel_color);

        }
    }

    return 0;
}