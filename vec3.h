#include <cmath>

struct vec3 {
    double x, y, z;
    vec3() : x(0), y(0), z(0) {}
    vec3(double a, double b, double c) : x(a), y(b), z(c) {}
    
    double length() const {
        return std::sqrt(x*x + y*y + z*z);
    }
};