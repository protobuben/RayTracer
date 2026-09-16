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
 
void export_series(const hittable& world, const blackhole& bh, const vec3& light_direction, 
    int samples, int frames, double max_rapidity, bool ping_pong, cam_config& cfg) {
    std::filesystem::create_directory("frames");
 
    for (int i = 0; i < frames; i++) {
        const double rapidity = max_rapidity * i / double(frames - 1);
        const double beta     = std::tanh(rapidity);
        cfg.beta = beta;

        std::ofstream out(frame_path(i));
        camera cam(cfg);
        render(out, cam, world, light_direction, bh, samples);
 
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
}

int main() {
    blackhole bh;
    const vec3 light_direction = vec3(.0, -1.0, -1);
    
    const vec3 eye(0.0, 0.2, 16.0);
    cam_config cfg(
        unit_vec3(bh.center - eye), // look at
        1200/5, // x
        500/5, // y
        eye, // from
        vec3(), // vel dir
        0.0 // beta
    );

    const int samples = 4;
 
    // export_series
    const int frames = 60;
    const double max_rapidity = 1;
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


    world.add(std::make_shared<disk>(bh.center, unit_vec3(vec3(-.07, 1, 0)), 3.0*bh.rs, 14.0*bh.rs, 420.0, 690.0));
    
    // world.add(std::make_shared<sphere>(vec3(1,0,-2), 3, 500));

    // sphere grid
    // for (int i = 0; i< 10; i++){
    //     for (int j = 0; j< 10; j++){
    //         world.add(std::make_shared<sphere>(vec3(-9+2*i, -9+2*j, 3), .5, 440 + 10*(i+j)));
    //         cerr_vec3(vec3(-10+2*i, -10+2*j, 3));
    //     }
    // }

    export_ppm(world, bh, light_direction, samples, cfg);
    // export_series(world, bh, light_direction, samples, frames, max_rapidity, ping_pong, cfg);

    return 0;
}