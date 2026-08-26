#pragma once
#include "vec3.h"
#include "ray.h"

struct hit_record {
    vec3 p, normal;
    double wavelength;
    double t;
};

struct hittable {
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    virtual ~hittable() = default;
};

