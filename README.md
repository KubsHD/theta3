# Theta2
Work in progress bullet hell wave shooter

## Prerequisites
- Visual Studio 2022 with C++ and CMake support (Windows) / Code editor of your choice (macOS)
- FMOD Core API installed for the target platform

## How to build
1. Clone the repository `git clone --recurse-submodules https://github.com/KubsHD/theta2`

#### Automatic build
2. Open cloned directory with Visual Studio
#### Manual build

2. Create build directory: `mkdir build && cd build`
3. Generate project files manually: `cmake .. -G "Ninja"`
4. Build: `ninja`

## Used libraries
- [imgui](https://github.com/ocornut/imgui)
- [SDL2](https://github.com/libsdl-org/SDL)
- [FMOD](https://fmod.com/)
- [cereal](https://github.com/USCiLab/cereal)
- [glm](https://github.com/g-truc/glm)
- [stb](https://github.com/nothings/stb)
- [json](https://github.com/nlohmann/json)
- [glad](https://glad.dav1d.de/)



