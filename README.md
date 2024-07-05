# Hard Clip

A VST to completely hard clip audio. This will serve as a demo Juce plugin for any of my future plugins.

## Dependencies

To build Hard Clip, you will need:

* [git](https://github.com/git-for-windows/git/releases/latest/)
* [CMake](https://cmake.org/download/)
* [Microsoft C++ compiler](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2017)

Hard Clip is only configured to build on Windows. It may or may not build on Mac or Linux.

## Building

To build Hard Clip, run the following commands from the root of the repository:

```bash
git submodule update --init # Download JUCE
cmake -S . -B build # Configure the build
cmake --build build # Build
```
