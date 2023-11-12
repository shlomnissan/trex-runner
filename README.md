# 🦖 Chrome’s Dinosaur Game in Modern C++

<p align="center">
   <img src="https://user-images.githubusercontent.com/3165988/120908452-565aa900-c61f-11eb-849c-7f56629657c0.gif" />
</p>

This repository contains a port of Chrome's Dinosaur Game written in modern C++. It uses modern CMake for build generation and Conan 2 as its package manager.

### Notes
- The original JavaScript source code for this game can be found [here](https://source.chromium.org/chromium/chromium/src/+/master:components/neterror/resources/offline.js).
- This port is accurate except for the missing Pterodactyl obstacle and night mode.

### Dependencies
All dependencies for this project are imported using Conan 2.
- `fmt/8.1.1` is used for string formatting.
- `rapidjson/1.1.0` is used for reading JSON configuration files.
- `sdl/2.26.5` is used for cross-platform system facilities.

This package also includes the `libs/stb_image.h` header for loading image files.

### Getting started
Make sure you have Conan 2 and CMake installed on your system.
<pre>
<b>$</b> git clone https://github.com/shlomnissan/trex-runner.git
<b>$</b> cd trex-runner
<b>$</b> conan install . --output-folder=build -b=missing -s=build_type=Debug
<b>$</b> cd build
<b>$</b> cmake .. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug
<b>$</b> cmake --build .
</pre>

Following these commands should result in an executable called `trex-runner` in the build directory. If you encounter any issues with Conan, take a look at the [Build a Simple CMake Project using Conan](https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html) tutorial, which will guide you through this process step-by-step.

## Licence

```
    ____       __                             __  
   / __ )___  / /_____ _____ ___  ____ ______/ /__
  / __  / _ \/ __/ __ `/ __ `__ \/ __ `/ ___/ //_/
 / /_/ /  __/ /_/ /_/ / / / / / / /_/ / /  / ,<   
/_____/\___/\__/\__,_/_/ /_/ /_/\__,_/_/  /_/|_|  
                                                  
Copyright (c) 2023-present Shlomi Nissan
https://betamark.com

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
