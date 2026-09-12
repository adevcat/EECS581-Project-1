# EECS581-Project-1

To Build:
Dependencies:
Qt: https://www.qt.io/development/download
cMake: https://cmake.org/download/

If QT is installed in a place different than the Path defined in CMakePresets.json, create a cmakeuserpresets.json and override the build paths. Must be built with the compiler bundled with qt. 

Executable must be ran in the same directory as bundled libraries; if you are on linux or macOS, you must manually add the required libraries to the directory.  

To build: 
cmake --preset default --fresh
cmake --build build
