#pragma once
#include "vec3.h"
#include "ray.h"

struct camera { 
    vec3 origin = vec3();
    int resX, resY;
    double height = 2;
    double width = height * double(resX)/resY;
    vec3 viewport_u = vec3(width, 0.0, 0.0);
    vec3 viewport_v = vec3(0.0, -height, 0.0);
    vec3 step_x = viewport_u/resX;
    vec3 step_y = viewport_v/resY;
    vec3 pixel00 = .5*(step_x+step_y);
    vec3 top_left = pixel00 + vec3(-width/2, height/2, -1);
    
    camera(): resX(800), resY(600) {};
    camera(int x, int y): resX(x), resY(y) {};

    ray project(int x, int y) {
        return ray(origin, top_left + step_x*x + step_y*y);
    }
};