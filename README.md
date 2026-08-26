# Ray tracer
A ray tracer built as a platform for visualising relativistic effects -
special relativity first, then geodesic tracing in curved spacetime.

The personal reason for this project is to actually see what happens at different speeds, rather than taking facts from books as is.

### Current state:
doppler effect demonstration on speeds $\beta = 0$, $0.1$, $0.2$ and $0.3$, camera movement vector (0, 0, -1) - forward, light_direction = (-1, -1, -0.5):

| β = 0 | β = 0.1 |
|:---:|:---:|
| ![doppler shift at beta=0](renders/doppler_00.png) | ![doppler shift at beta=0.1](renders/doppler_01.png) |

| β = 0.2 | β = 0.3 |
|:---:|:---:|
| ![doppler shift at beta=0.2](renders/doppler_02.png) | ![doppler shift at beta=0.3](renders/doppler_03.png) |


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

## Rendering improvements
Independent of the physics track above

- [ ] Point light sources with distance falloff
- [ ] Emissive objects (visible light sources)
- [ ] Reflections (recursive ray_color)
- [ ] Full spectral rendering instead of single wavelength
- [ ] Multithreading (std::thread over scanlines)
- [ ] GPU port
- [ ] Real-time viewer with free camera

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
