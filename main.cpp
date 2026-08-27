#include <iostream>
#include <fstream>
#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "hittable.h"
#include <vector>
#include <memory>
#include "hittable_list.h"
#include "renderer.h"
#include "color.h"

int main() {
    std::ofstream out("image.ppm");
    const vec3 light_direction = vec3(-1.0, -1.0, -.5);

    hittable_list world;
    world.add(std::make_shared<sphere>(vec3(0,0,-1), 0.5, 500));
    world.add(std::make_shared<sphere>(vec3(-6,1,-5), 2, 600));
    world.add(std::make_shared<sphere>(vec3(-.2,.3,-.9), 0.3, 575));
    world.add(std::make_shared<sphere>(vec3(.2,-.3,-.9), 0.3, 400));
    world.add(std::make_shared<sphere>(vec3(.4,-.2,-1), 0.4, 525));
    
    world.add(std::make_shared<plane>(vec3(2, -.6, 2), vec3(-.3,.3,-.6), .1, .2, 725));
    world.add(std::make_shared<plane>(vec3(-2, 3, 0.8), vec3(.5,-0.3,-.6), .1, .2, 545));
    world.add(std::make_shared<plane>(vec3(0.1, -.3, 0.8), vec3(0.4,-0.6,-.8), .6, .4, 450));

    world.add(std::make_shared<plane>(vec3(0, 1, 0), vec3(0, -1,-1), 5, 5, 575));
    world.add(std::make_shared<plane>(vec3(-1, .5, 2), vec3(5,1,-7), 3, 3, 575));

    camera cam(360, 240, vec3(-.5, 0.5, 0.5), unit_vec3(vec3(1.0,0.0,-1.0)), 0.5);
    render(out, cam, world, light_direction);
    return 0;
}