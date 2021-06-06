# 🦖 T-Rex Runner! (ported to C)

![trex](https://user-images.githubusercontent.com/3165988/120908452-565aa900-c61f-11eb-849c-7f56629657c0.gif)

This is a C port of Chrome's offline T-Rex Runner ([source-code](https://source.chromium.org/chromium/chromium/src/+/master:components/neterror/resources/offline.js;l=7?q=t-rex%20package:%5Echromium$&ss=chromium)).

The port is missing a few game elements, but it's otherwise accurate:
- It's missing night mode.
- It's missing the Pterodactyl obstacle.
- It has a slightly different intro.

The build is generated using CMake, and the only dependency is SDL (including the image and mixer libraries).

### MIT license:

```
Copyright (c) 2021 Shlomi Nissan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
