#pragma once
#include "vec3.h"

struct blackhole {
    vec3 center = vec3(0.0, 0.0, 0.0);
    double rs = 1.0;
    double h = .05;
    double escape_r = 35.0;
    int max_steps = 4000;
};