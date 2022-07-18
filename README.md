# LLGL - Low Level Game Loop

LLGL is a rendering engine and an abstraction layer for OS-specific things like windowing, keyboard/mouse events etc. It uses OpenGL and SDL as the backend.

## Simple install

* Install SDL2, SDL2_ttf, SDL2_image and GLEW

```sh
# Ubuntu
sudo apt install ninja-build libsdl2-dev libsdl2-ttf-dev libglew-dev
```

* Clone the repository

```sh
git clone https://github.com/sppmacd/llgl
```

* Download, build and install EssaUtil

EssaUtil is a general-purpose helper library that is used in ESSA products.

```sh
git clone https://github.com/essa-software/util
cd util
./install.sh
cd ..
```

* Install LLGL (This performs a default CMake installation).

```sh
cd llgl
./install.sh
```
