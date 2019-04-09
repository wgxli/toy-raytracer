# Toy Raytracer
Toy raytracer I wrote in C++ back in 2015.

![Sample output image.](https://raw.githubusercontent.com/wgxli/toy-raytracer/master/output.png)

## Features
* Accurate treatment of reflective, refractive, and diffuse surfaces, including Fresnel interactions.
* Depth of field
* Adaptive sampling (samples increased on noisy pixels)
* Probably some more things that I forgot about since 2015

## Requirements
Works out-of-the box on Linux with g++ installed.
Shouldn't be too hard to run on Windows.

## Usage
### Basic Setup
1. Run `./compile.sh`. All this does is compile all `.cpp` files in the `./src` directory.
2. To render a sample image, run `./render.sh`. This may take a few minutes (go and have a coffee). The output will be written to `output.bmp`.
3. To render an animation, run `./animate.sh`. This may take a nontrivial amount of time. The output will be unceremoniously dumped to several dozen `.bmp` files.

### Customization
* All setup is located in `main.cpp` (for stills) and `animation.cpp` (for animations).
* Definitions for polyhedral meshes (i.e. the cube) is stored in `meshData.h`.
