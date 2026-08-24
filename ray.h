#pragma once
#include "vec3.h"

struct ray {
    vec3 origin, direction;
    
    ray() : origin(vec3()), direction(vec3()) {}
    ray(const vec3& orig, const vec3& dir) : origin(orig), direction(dir) {}
    vec3 at(double t) const { return origin + t*direction; }
};