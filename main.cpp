#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <cmath>
#include <vector>
#include <memory>

#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "hittable.h"
#include "hittable_list.h"
#include "renderer.h"
#include "color.h"

std::string frame_path(int i) {
    std::ostringstream s;
    s << "frames/f" << std::setw(3) << std::setfill('0') << i << ".ppm";
    return s.str();
}

int main() {
    const int frames = 60;
    const double max_rapidity = 1;
    const int samples = 8;
    const bool ping_pong = true;
    const vec3 res(720, 480, 0);

    std::filesystem::create_directory("frames");

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
    // world.add(std::make_shared<plane>(vec3(0.0, 0.0, 1.0), vec3(0, 0, -15), 20, 20, 650));

    for (int i = 0; i < frames; i++) {
        const double rapidity = max_rapidity * i / double(frames - 1);
        const double beta     = std::tanh(rapidity);

        std::ofstream out(frame_path(i));
        camera cam(res.x, res.y, vec3(-.5, 0.5, 0.5), unit_vec3(vec3(1.0, 0.0, -1.0)), beta);
        render(out, cam, world, light_direction, samples);

        std::cerr << "\rframe " << (i + 1) << "/" << frames
                  << "  beta=" << beta << "          \n";
    }

    if (ping_pong) {
        for (int i = frames - 2; i >= 1; i--) {
            const int j = 2 * frames - 2 - i;
            std::filesystem::copy_file(frame_path(i), frame_path(j),
                std::filesystem::copy_options::overwrite_existing);
        }
        std::cerr << "mirrored to " << (2 * frames - 2) << " frames\n";
    }

    return 0;
}