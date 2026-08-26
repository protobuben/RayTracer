# Ray tracer
A ray tracer built as a platform for visualising relativistic effects -
special relativity first (aberration, Doppler shift, beaming), then
geodesic tracing in curved spacetime.

![doppler effect at speed beta=0](renders/doppler_00.png)
![doppler effect at speed beta=0.1](renders/doppler_01.png)
![doppler effect at speed beta=0.2](renders/doppler_02.png)
![doppler effect at speed beta=0.3](renders/doppler_03.png)


### Plan
- [x] PPM output
- [x] Sphere intersection
- [x] Lambertian shading
- [x] Hittable abstraction
- [x] Shadows 
- [x] Coloring
- [ ] SR: [aberration](./docs/aberration.md), Doppler, beaming
- [ ] Schwarzschild geodesics
- [ ] Kerr

## Usage
Program outputs a .ppm file. Can be opened in VSCode via [Extension](https://marketplace.visualstudio.com/items?itemName=ngtystr.ppm-pgm-viewer-for-vscode)

## Build
```
g++ -O2 -Wall main.cpp -o main.exe
./main.exe
```

## Archive
![sphere_detection](renders/sphere_detection.png)
![Lambertian_shading_on_a_sphere](renders/Lambertian_shading_on_a_sphere.png)
![sphere_cluster](renders/sphere_cluster.png)
![planes](renders/planes.png)
![shadows](renders/shadows.png)
![colors](renders/colors.png)
![smooth_colors](renders/smooth_colors.png)
![left_forward_at_beta_08](renders/left_forward_at_beta_08.png)
