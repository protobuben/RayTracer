#pragma once
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

struct plane : public hittable {

    vec3 norm, origin;
    double displacement;
    double size_x, size_y;
    vec3 color;
    vec3 u, v;
    
    plane(const vec3& c, vec3 o, double x, double y, vec3 col = vec3(1.0,1.0,1.0)) : norm(unit_vec3(c)), origin(o), size_x(x), size_y(y), color(col) {
        displacement = dot(norm, origin);
        vec3 u_0 = vec3(0.0, 1.0, 0.0);
        if (std::fabs(dot(norm, u_0)) > 0.9) { u_0 = vec3(1.0, 0.0, 0.0); }
        u = unit_vec3(u_0 - dot(u_0, norm) * norm);
        v = cross(norm, u);
    };
    
    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        const double numerator = displacement-dot(norm, r.origin);
        const double denominator = dot(norm, r.direction);
        if (std::fabs(denominator) < 1e-8) { return false; }
        double t = numerator/denominator;

        if (t < t_min || t > t_max) { 
            return false;
        }

        const vec3 point = r.at(t);
        const vec3 w = point - origin;
        const double x_proj = dot(w, u);
        const double y_proj = dot(w, v);
        if (std::fabs(x_proj) > size_x) { return false; }
        if (std::fabs(y_proj) > size_y) { return false; }

        rec.t = t;
        rec.p = point;
        rec.normal = norm;
        rec.color = color;
        return true;
    }
};