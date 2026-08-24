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

int main() {
    std::ofstream out("image.ppm");
    const int horizontal = 800;
    const int vertical = 600;
    out << "P3\n" << horizontal << " " << vertical << "\n255\n";

    camera cam(horizontal, vertical);

    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {

            const ray r = cam.project(i, j);
            const vec3 dir = unit_vec3(r.direction);
            const double a = 0.5*(dir.y + 1.0);
            vec3 pixel_color = a*vec3(1.0, 0.0, 1.0);
            write_color(out, pixel_color);

        }
    }

    return 0;
}