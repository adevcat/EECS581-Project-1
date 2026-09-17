# EECS581-Project-1

## Dependencies

### Windows
- **Qt6**: https://www.qt.io/development/download
- **CMake**: https://cmake.org/download/

### Linux
- **Qt6**: https://www.qt.io/development/download
- **CMake**: `sudo apt install cmake`
- **OpenGL**: `sudo apt install libgl1-mesa-dev`

## Setup Notes

- If Qt is installed in a location different from the path defined in `CMakePresets.json`, create a `CMakeUserPresets.json` and override the relevant build paths.
- The project must be built with the compiler bundled with Qt.
- The executable must be run from the same directory as its bundled libraries. On windows, this is automatically done via `windeployqt` as part of the build script.

## Build Instructions

### Windows
```bash
cmake --preset default --fresh
cmake --build build
```

### Linux
```bash
cmake --preset default-linux --fresh
cmake --build build
```
