#pragma once
#include "vec3.h"
#include "ray.h"
#include "constants.h"
#include "relativity.h"

struct cam_config {
    vec3 origin, look_at;
    int resX, resY;
    vec3 velocity_dir;
    double beta;
    cam_config(const vec3& target, int x = 800, int y = 600, const vec3& o = vec3(), const vec3& veld = vec3(0,0,-1), double b = 0)
    :  look_at(target), origin(o), resX(x), resY(y), velocity_dir(veld), beta(b) {}
};

struct camera { 
    vec3 origin, look_at;
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
    vec3 fwd, right, up;

    vec3 velocity_dir;
    double beta;
    
    camera(const cam_config& cfg)
    : origin(cfg.origin), resX(cfg.resX), resY(cfg.resY), look_at(cfg.look_at), velocity_dir(cfg.velocity_dir), beta(cfg.beta) {
        fwd = unit_vec3(look_at - origin);
        const vec3 ref = (std::fabs(fwd.y) > 0.999) ? vec3(0,0,1) : vec3(0,1,0);
        right = unit_vec3(cross(fwd, ref));
        up = cross(right, fwd);
    };

    ray project(int x, int y, double dx = 0, double dy = 0) const {
        const double px = (2.0*(x + 0.5 + dx)/resX - 1.0) * (width/2.0);
        const double py = (1.0 - 2.0*(y + 0.5 + dy)/resY) * (height/2.0);
        const vec3 d = unit_vec3(focus_length*fwd + px*right + py*up);
        return ray(origin, aberrate(d, velocity_dir, beta));
    }
};