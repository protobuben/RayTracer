#include <iostream>
#include <fstream>

#include "vec3.h"


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


    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {

            const double r = double(i)/(horizontal-1);
            const double b = double(j)/(vertical-1);


            vec3 pixel_color(r, 0.0, b);
            write_color(out, pixel_color);

        }
    }

    return 0;
}