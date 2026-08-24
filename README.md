# Ray tracer
A ray tracer built as a platform for visualising relativistic effects -
special relativity first (aberration, Doppler shift, beaming), then
geodesic tracing in curved spacetime.

![Current state](renders/planes.png)

### Plan
- [x] PPM output
- [x] Sphere intersection
- [x] Lambertian shading
- [x] Hittable abstraction
- [ ] SR: aberration, Doppler, beaming
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
![Sphere intersection](renders/sphere_detection.png)
![Lambertian shading on a sphere](renders/Lambertian_shading_on_a_sphere.png)
![Current state](renders/sphere_cluster.png)
