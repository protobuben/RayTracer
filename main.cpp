#include <iostream>
#include <fstream>
#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "hittable.h"


void write_color(std::ostream& out, const vec3& pixel_color) {

    const int r = static_cast<int>(255.999*pixel_color.x);
    const int g = static_cast<int>(255.999*pixel_color.y);
    const int b = static_cast<int>(255.999*pixel_color.z);

    out << r << " " << g << " " << b << "\n";
}

int main() {
    std::ofstream out("image.ppm");
    const int horizontal = 320;
    const int vertical = 240;
    const vec3 light_direction = vec3(-1.0, -1.0, -.5);

    sphere s(vec3(0,0,-1), .5);
    out << "P3\n" << horizontal << " " << vertical << "\n255\n";

    camera cam(horizontal, vertical);

    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {
            vec3 pixel_color;
            const ray r = cam.project(i, j);

            hit_record record;

            if (s.hit(r, 0.001, 1e9, record)) {
                const double brightness = std::max(dot(-light_direction, record.normal), 0.0);
                pixel_color = vec3(1.0, 1.0, 1.0) * (.1 + .9*brightness);

            } else {
                pixel_color = vec3(0.0, 0.0, 0.0);    
            }
            
            write_color(out, pixel_color);

        }
    }

    return 0;
}