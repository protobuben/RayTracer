
#pragma once
#include "vec3.h"
#include "schwarzschild.h"
#include <cmath>

struct geo_frame { vec3 u, w; };

inline vec3 to_cartesian(const gstate& s, const vec3& hole, const geo_frame& fr) {
    const double r = s.x[1], th = s.x[2], ph = s.x[3];
    return hole + r*(std::cos(ph)*fr.u + std::sin(ph)*fr.w);
    // const double sinth = std::sin(th);
    // return vec3(r*sinth*std::cos(ph), r*sinth*std::sin(ph), r*std::cos(th)) + hole;
}

inline gstate from_camera_to_gstate(const vec3& origin, const vec3& dir, const vec3& hole, double rs, geo_frame& fr) {
    const vec3 hole_centered = origin - hole;
    const vec3 d = unit_vec3(dir);
    const double r = hole_centered.length();

    fr.u = hole_centered/r;
    vec3 perp = d - dot(d, fr.u)*fr.u;
    double pl = perp.length();
    if (pl < 1e-12) {
        vec3 a = (std::fabs(fr.u.x) < 0.9) ? vec3(1,0,0) : vec3(0,1,0);
        fr.w = unit_vec3(a - dot(a, fr.u)*fr.u);
        pl = 0.0;
    } else {
        fr.w = perp / pl;
    }

    gstate s;
    s.x[0] = 0.0; s.x[1] = r; s.x[2] = pi/2; s.x[3] = 0.0;
    s.v[1] = dot(d, fr.u);
    s.v[2] = 0.0;
    s.v[3] = pl/r;

    const double f = 1.0 - rs/r;
    s.v[0] = std::sqrt((s.v[1]*s.v[1]/f + r*r*s.v[3]*s.v[3])/f);

    return s;
}

// inline gstate from_camera_to_gstate(const vec3& origin, const vec3& dir, const vec3& hole, double rs) {
//     const vec3 hole_centered = origin - hole;

//     const double r = hole_centered.length();
//     const double th = std::acos(hole_centered.z/r);
//     const double ph = std::atan2(hole_centered.y, hole_centered.x);

//     const double sinth = std::sin(th), costh = std::cos(th);
//     const double sinph = std::sin(ph), cosph = std::cos(ph);

//     const double d_r = dir.x*sinth*cosph + dir.y*sinth*sinph + dir.z*costh;
//     const double d_th = dir.x*costh*cosph + dir.y*costh*sinph - dir.z*sinth;
//     const double d_ph = -dir.x*sinph + dir.y*cosph;
    
//     gstate s;
//     s.x[0] = 0; s.x[1] = r; s.x[2] = th; s.x[3] = ph;

//     s.v[1] = d_r;
//     s.v[2] = d_th / r;
//     s.v[3] = d_ph / (r*sinth);
    
//     const double f = (1.0 - rs/r);
//     const double spatial = s.v[1]*s.v[1]/f
//                          + r*r*s.v[2]*s.v[2]
//                          + r*r*sinth*sinth*s.v[3]*s.v[3];
//     s.v[0] = std::sqrt(spatial / f);

//     return s;
// }