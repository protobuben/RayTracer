#pragma once
#include "vec3.h"
#include "ray.h"

struct camera { 
    vec3 origin;
    int resX, resY;
    double focus_length = 1;
    double height = 2;
    double width = height * double(resX)/resY;
    vec3 viewport_u = vec3(width, 0.0, 0.0);
    vec3 viewport_v = vec3(0.0, -height, 0.0);
    vec3 step_x = viewport_u/resX;
    vec3 step_y = viewport_v/resY;
    vec3 pixel00 = .5*(step_x+step_y);
    vec3 top_left = pixel00 + vec3(-width/2, height/2, -focus_length);
    
    camera(int x = 800, int y = 600, vec3 o = vec3()): resX(x), resY(y), origin(o) {};

    ray project(int x, int y) const {
        return ray(origin, top_left + step_x*x + step_y*y);
    }
};