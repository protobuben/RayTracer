#pragma once
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "blackhole.h"

struct disk : public hittable {
    vec3 center, normal;
    double r_in, r_out;
    double lambda_in, lambda_out;
    double rs;

    disk(const blackhole& bh, const vec3& c, const vec3& n, double ri, double ro, double lin = 450.0, double lout = 700)
        : rs(bh.rs), center(c), normal(n), r_in(ri), r_out(ro), lambda_in(lin), lambda_out(lout) {}
    
    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        const double denom = dot(normal, r.direction);
        if (std::fabs(denom) < 1e-9) return false;

        const double t = dot(normal, center - r.origin) /denom;
        if (t < t_min || t> t_max) return false;

        const vec3 p = r.at(t);
        const double rr = (p - center).length();
        if (rr < r_in || rr > r_out) return false;

        rec.t = t;
        rec.p = p;
        rec.normal = (denom < 0.0) ? normal : -normal;

        const double x = (rr - r_in) / (r_out - r_in);
        
        rec.wavelength = 580;
        rec.emissive = true;

        const double f = 1 - rs/rr;
        const double v = std::sqrt(rs/(2*rr*f));
        rec.velocity = v * unit_vec3(cross(normal, p-center));

        return true;
    }
};

