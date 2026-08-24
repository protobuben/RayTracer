#pragma once
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

struct sphere : public hittable {
    vec3 center;
    double radius;

    sphere(const vec3& c, double r) : center(c), radius(r) {};

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        const vec3 distance = r.origin - center;
        const double a = r.direction.dot_self();
        const double h = dot(r.direction, distance);
        const double c = distance.dot_self() - radius*radius;
        const double discr = h*h-a*c;
        if (discr < 0) return false;

        const double sqrtd_part = std::sqrt(discr)/a;
        const double other_part = -h/a;
        double t = other_part - sqrtd_part;

        if (t < t_min || t > t_max) { 
            t = other_part + sqrtd_part;
            if (t < t_min || t > t_max) { return false; }
        }
        rec.t = t;
        rec.p = r.at(t);
        rec.normal = (rec.p - center)/radius;
        return true;
    }
};