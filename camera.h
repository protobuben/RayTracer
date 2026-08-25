#pragma once
#include "vec3.h"
#include "ray.h"
#include "constants.h"
#include "relativity.h"

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

    vec3 velocity_dir;
    double beta;
    
    camera(int x = 800, int y = 600, const vec3& o = vec3(), const vec3& veld = vec3(0,0,-1), double b = 0): resX(x), resY(y), origin(o), velocity_dir(veld), beta(b) {};

    ray project(int x, int y, double dx = 0, double dy = 0) const {
        return ray(origin, aberrate(unit_vec3(top_left + step_x*(x + dx) + step_y*(y + dy)), velocity_dir, beta));
    }
};