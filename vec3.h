#pragma once
#include <cmath>

struct vec3 {
    double x, y, z;
    vec3() : x(0.0), y(0.0), z(0.0) {}
    vec3(double a, double b, double c) : x(a), y(b), z(c) {}
    
    double length() const { return std::sqrt(x*x + y*y + z*z); }
    double dot_self() const { return x*x + y*y + z*z; }
    vec3 operator-() const { return vec3(-x, -y, -z); }
    vec3& operator+=(const vec3& v) { x += v.x; y += v.y; z+=v.z; return *this; }
    vec3& operator*=(double t) { x *= t; y *= t; z *= t; return *this; }
};

inline vec3 operator+(const vec3& u, const vec3& v) { return vec3(u.x+v.x, u.y+v.y, u.z+v.z); }
inline vec3 operator-(const vec3& u, const vec3& v) { return vec3(u.x-v.x, u.y-v.y, u.z-v.z); }

inline vec3 operator*(double t, const vec3& v) { return vec3(t*v.x, t*v.y, t*v.z); }
inline vec3 operator*(const vec3& v, double t) { return t*v; }
inline vec3 operator*(const vec3& u, const vec3& v) { return vec3(u.x*v.x, u.y*v.y, u.z*v.z); }

inline vec3 operator/(const vec3& v, double t) { return (1.0/t)*v; }

inline vec3 unit_vec3(const vec3& v) { return v/v.length(); }

inline double dot(const vec3& u, const vec3& v) { return u.x*v.x + u.y*v.y + u.z*v.z; }
inline vec3 cross(const vec3& u, const vec3& v) { return vec3(u.y*v.z - v.y*u.z, u.z*v.x - v.z*u.x, u.x*v.y - v.x*u.y); }

