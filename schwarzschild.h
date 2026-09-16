#pragma once
#include <cmath>
struct gstate {
    double x[4]; // t, r, theta, phi
    double v[4]; // d/dlambda
};

inline void geodesic_rhs(const gstate& s, double rs, double dv[4]) {
    const double r = s.x[1], th = s.x[2];
    const double dt = s.v[0], dr = s.v[1], dph = s.v[3];
    // const double sinth = std::sin(th);

    const double Г_t_rt = rs/(2*r*(r-rs));

    const double Г_r_tt = rs*(r-rs)/(2*r*r*r);
    const double Г_r_rr = -rs/(2*r*(r-rs));
    // const double Г_r_thth = rs - r;
    const double Г_r_phph = rs - r; //(rs-r)*sinth*sinth;

    // const double Г_th_rth = 1/r;
    // const double Г_th_phph = -sinth*std::cos(th);

    const double Г_ph_rph = 1.0/r;
    // const double Г_ph_thph = 1/std::tan(th);
    
    
    dv[0] = -2*Г_t_rt*dr*dt;
    dv[1] = -Г_r_tt*dt*dt - Г_r_rr*dr*dr - Г_r_phph*dph*dph;
    dv[2] =  0.0;
    dv[3] = -2*Г_ph_rph*dr*dph;
    
    // without theta fixed
    // dv[0] = -2*Г_t_rt*dr*dt;
    // dv[1] = -Г_r_tt*dt*dt - Г_r_rr*dr*dr - Г_r_thth*dth*dth - Г_r_phph*dph*dph;
    // dv[2] = -2*Г_th_rth*dr*dth - Г_th_phph*dph*dph;
    // dv[3] = -2*Г_ph_rph*dr*dph - 2*Г_ph_thph*dth*dph;
}

inline void rk4_step(gstate& s, double rs, double h) {
    double k1v[4], k2v[4], k3v[4], k4v[4];
    gstate tmp;

    // k1
    geodesic_rhs(s, rs, k1v);
    const double* k1x = s.v;

    // k2
    for (int i = 0; i < 4; i++) {
        tmp.x[i] = s.x[i] + .5 * h * k1x[i];
        tmp.v[i] = s.v[i] + .5 * h * k1v[i];
    }
    geodesic_rhs(tmp, rs, k2v);
    double k2x[4]; for (int i = 0; i < 4; i++) k2x[i] = tmp.v[i];

    // k3
    for (int i = 0; i < 4; i++) {
        tmp.x[i] = s.x[i] + .5 * h * k2x[i];
        tmp.v[i] = s.v[i] + .5 * h * k2v[i];
    }
    geodesic_rhs(tmp, rs, k3v);
    double k3x[4]; for (int i = 0; i < 4; i++) k3x[i] = tmp.v[i];

    // k4
    for (int i = 0; i < 4; i++) {
        tmp.x[i] = s.x[i] + h * k3x[i];
        tmp.v[i] = s.v[i] + h * k3v[i];
    }
    geodesic_rhs(tmp, rs, k4v);
    double k4x[4]; for (int i = 0; i < 4; i++) k4x[i] = tmp.v[i];

    for (int i = 0; i < 4; i++) {
        s.x[i] += (h/6) * (k1x[i] + 2 * k2x[i] + 2 * k3x[i] + k4x[i]);
        s.v[i] += (h/6) * (k1v[i] + 2 * k2v[i] + 2 * k3v[i] + k4v[i]);
    }
}

inline double null_residual(const gstate& s, double rs) { // g_{\mu\nu}v^\mu v^\nu shall stay close to 0
    const double r = s.x[1], th = s.x[2];
    const double f = 1.0 - rs/r;
    const double sinth = std::sin(th);
    return -f*s.v[0]*s.v[0] + s.v[1]*s.v[1]/f + s.v[1]*s.v[1]*s.v[3]*s.v[3];
    // return -f*s.v[0]*s.v[0]
    //       + s.v[1]*s.v[1]/f
    //       + r*r*s.v[2]*s.v[2]
    //       + r*r*sinth*sinth*s.v[3]*s.v[3];
}
