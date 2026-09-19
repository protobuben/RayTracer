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
#include "disk.h"
#include "plane.h"
#include "hittable.h"
#include "hittable_list.h"
#include "renderer.h"
#include "color.h"
#include "blackhole.h"

std::string frame_path(int i) {
    std::ostringstream s;
    s << "frames/f" << std::setw(3) << std::setfill('0') << i << ".ppm";
    return s.str();
}

void export_ppm(const hittable& world, const blackhole& bh, const vec3& light_direction,
    int samples, const cam_config& cfg) {
    std::ofstream out("image.ppm");
    camera cam(cfg);
    render(out, cam, world, light_direction, bh, samples);
 
    std::cerr << "\rwrote image.ppm  beta=" << cfg.beta << "          \n";
}

int WORKER_COUNT = 1;
int WORKER_INDEX = 1;

 
void export_series(const hittable& world, const blackhole& bh, const vec3& light_direction, 
    int samples, int frames, cam_config& end_params, bool ping_pong, cam_config& cfg) {
    std::filesystem::create_directory("frames");
    
    auto lerp = [](double a, double b, double alpha) { return a*(1-alpha) + b*alpha; };
    // resolution must land on an exact integer every frame: a*(1-t)+b*t is not
    // exactly a when a==b, and truncating 191.99999999999997 gives 191, which
    // changes the frame size mid-sequence and breaks the gif filter graph.
    auto lerp_int = [&](int a, int b, double alpha) { return int(std::lround(lerp(a, b, alpha))); };

    double start_rapidity = std::atanh(cfg.beta);
    double end_rapidity = std::atanh(end_params.beta);

    for (int i = 0; i < frames; i++) {
        if (i%WORKER_COUNT != WORKER_INDEX) { continue; }

        const double alpha = i / double(frames - 1);
        double new_beta = std::tanh(lerp(start_rapidity, end_rapidity, alpha));
        const cam_config temp(
            lerp_vec3(cfg.look_at, end_params.look_at, alpha), // look at
            cfg.resX, // x
            cfg.resY, // y
            lerp_vec3(cfg.origin, end_params.origin, alpha), // from
            lerp_vec3(cfg.velocity_dir, end_params.velocity_dir, alpha), // vel dir
            new_beta // beta
        );

        std::ofstream out(frame_path(i));

        camera cam(temp);
        render(out, cam, world, light_direction, bh, samples);
 
        std::cerr << "\rframe " << (i + 1) << "/" << frames << "  beta=" << new_beta << "\n";
    }

    // if (ping_pong) {
    //     for (int i = frames - 2; i >= 1; i--) {
    //         const int j = 2 * frames - 2 - i;
    //         std::filesystem::copy_file(frame_path(i), frame_path(j),
    //             std::filesystem::copy_options::overwrite_existing);
    //     }
    //     std::cerr << "mirrored to " << (2 * frames - 2) << " frames\n";
    // }
}

int main(int argc, char** argv) {
    if (argc>=3) {
        WORKER_COUNT = std::stoi(argv[2]);
        WORKER_INDEX = std::stoi(argv[1]);
    }
    

    blackhole bh;
    const vec3 light_direction = vec3(.0, -1.0, -1);
    
    const vec3 eye(0.0, 3.0, 9.0);
    const double resX = 1920;
    const double resY = 1080;
    
    cam_config cfg(
        bh.center-eye, // look at
        resX, // x
        resY, // y
        eye, // from
        vec3(-1, 0, -1), // vel dir
        0.0 // beta
    );

    cam_config end_cfg(
        bh.center-eye/4, // look at
        resX, // x
        resY, // y
        eye/4, // from
        vec3(-1, 0, -1), // vel dir
        0.0 // beta
    );

    const int samples = 8;
 
    // export_series
    const int frames = 240;
    const bool ping_pong = true;


    hittable_list world;
    // world.add(std::make_shared<sphere>(vec3(0,0,-1), 0.5, 500));
    // world.add(std::make_shared<sphere>(vec3(-6,1,-5), 2, 600));
    // world.add(std::make_shared<sphere>(vec3(-.2,.3,-.9), 0.3, 575));
    // world.add(std::make_shared<sphere>(vec3(.2,-.3,-.9), 0.3, 400));
    // world.add(std::make_shared<sphere>(vec3(.4,-.2,-1), 0.4, 525));

    // world.add(std::make_shared<plane>(vec3(2, -.6, 2), vec3(-.3,.3,-.6), .1, .2, 725));
    // world.add(std::make_shared<plane>(vec3(-2, 3, 0.8), vec3(.5,-0.3,-.6), .1, .2, 545));
    // world.add(std::make_shared<plane>(vec3(0.1, -.3, 0.8), vec3(0.4,-0.6,-.8), .6, .4, 450));

    // world.add(std::make_shared<plane>(vec3(0, 1, 0), vec3(0, -1,-1), 5, 5, 575));
    // world.add(std::make_shared<plane>(vec3(-1, .5, 2), vec3(5,1,-7), 3, 3, 575));
    // world.add(std::make_shared<plane>(vec3(0.0, 0.0, 1.0), vec3(0, 0, -15), 20, 20, 650));


    world.add(std::make_shared<disk>(bh, bh.center, unit_vec3(vec3(0, 1, 0)), 3.0*bh.rs, 14.0*bh.rs, 420.0, 690.0));
    
    // world.add(std::make_shared<sphere>(vec3(1,0,-2), 3, 500));

    // sphere grid
    // for (int i = 0; i< 10; i++){
    //     for (int j = 0; j< 10; j++){
    //         world.add(std::make_shared<sphere>(vec3(-9+2*i, -9+2*j, 3), .5, 440 + 10*(i+j)));
    //         cerr_vec3(vec3(-10+2*i, -10+2*j, 3));
    //     }
    // }

    // export_ppm(world, bh, light_direction, samples, cfg);
    export_series(world, bh, light_direction, samples, frames, end_cfg, ping_pong, cfg);

    return 0;
}