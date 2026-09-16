#pragma once
#include "vec3.h"

struct blackhole {
    vec3 center = vec3(10.0, 0.0, -10.0);
    double rs = 1.6;
    double h = .05;
    double escape_r = 40.0;
    int max_steps = 4000;
};