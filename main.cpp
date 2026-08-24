#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ray.h"
#include "camera.h"


void write_color(std::ostream& out, const vec3& pixel_color) {

    const int r = static_cast<int>(255.999*pixel_color.x);
    const int g = static_cast<int>(255.999*pixel_color.y);
    const int b = static_cast<int>(255.999*pixel_color.z);

    out << r << " " << g << " " << b << "\n";
}


bool hit_sphere(const vec3& center, double radius, const ray& r) {
    const vec3 distance = r.origin - center;
    const double a = r.direction.dot_self();
    const double b = 2 * dot(r.direction, distance);
    const double c = distance.dot_self() - radius*radius;
    const double discr = b*b-4*a*c;
    return discr>=0;
}


int main() {
    std::ofstream out("image.ppm");
    const int horizontal = 800;
    const int vertical = 600;
    out << "P3\n" << horizontal << " " << vertical << "\n255\n";

    camera cam(horizontal, vertical);

    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {
            vec3 pixel_color;
            const ray r = cam.project(i, j);

            if (hit_sphere(vec3(0,0,-1), .5, r)) {
                pixel_color = vec3(1.0, 1.0, 1.0);    
            } else {
                const vec3 dir = unit_vec3(r.direction);
                const double a = 0.5*(dir.y + 1.0);
                pixel_color = a*vec3(1.0, 0.0, 1.0);    
            }
            
            write_color(out, pixel_color);

        }
    }

    return 0;
}