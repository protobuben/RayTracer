#include <iostream>
#include <fstream>

int main() {
    std::ofstream out("image.ppm");
    const int horizontal = 800;
    const int vertical = 600;
    out << "P3\n" << horizontal << " " << vertical << "\n255\n";

    for (int j = 0; j < vertical; j++) {
        for (int i = 0; i < horizontal; i++) {
            const double r = double(i)/(horizontal-1);
            const double g = double(j)/(vertical-1);
            const int b = 0;

            const int ir = static_cast<int>(255.999*r);
            const int ig = static_cast<int>(255.999*g);

            out << ir << " " << ig << " 0\n";
        }
    }
    

    return 0;
}