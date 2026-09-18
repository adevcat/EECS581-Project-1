# EECS581 - Project-1: Minesweeper

**Team Members:** Will Godderz, Jaydee Brown, Lea Sulthana Syed, Aidan Bergeman, Zackary Rhodes, Ethan Gao, Didier Carrillo

**Creation Date:** 2026-09-09
**External Sources:** None

## Prerequisites & Dependencies
* **C++ Compiler:** C++17 compatible compiler (MinGW bundled with Qt recommended for Windows)
* **CMake:** Version 3.21 or higher ([Download](https://cmake.org/download/))
* **Qt6:** Widgets module ([Download](https://www.qt.io/development/download))

## Configuration & Build Instructions

1. **Toolchain & Path Setup:**
    If Qt is installed in a location different from the paths declared in `CMakePresets.json`, create a `CMakeUserPresets.json` file in the root directory to override the local paths without modifying tracked repo files.

2. **Configure the Project:**
    ```bash
    cmake --preset default --fresh

3. **Build the Executables:**
    ```bash
    cmake --build build

### Execution & Platform Notes
* The compiled executable is placed inside the`build/bin/` directory.

* **Windows:**
    * The build automatically runs `windeployqt` post-build to package the required Qt runtime DLL files alongside the executables.
    * Launch the game directly by running `build/bin/minesweeper.exe` or by extracting and running the generated `minesweeper.zip`.
* **Linux/macOS:**
    * Binaries must be run in the presence of the required Qt6 shared libraries.
    * Ensure Qt6 packages are installed via your package manager (ex: `qt6-base-dev` or Homebrew `qt@6`) or ensure `LD_LIBRARY_PATH` / dynamic linker paths include your Qt installation directory before launching:

    ```bash
    ./build/bin/minesweeper

## How to Play & Controls

1. **Start the Game:** Launch the application. The timer starts with your first move.
2. **Left-Click:** Uncover a tile.
    * Your first click is guaranteed to be safe.
    * If a tile touches zero adjacent mines, neighboring tiles reveal automatically.
    * Uncovering a mine results in an immediate game over.
3. **Right-Click:** Flag or unflag a tile to mark suspected mine locations. The remaining mine counter in the status bar updates accordingly.
4. **Winning:** Successfully uncover all safe tiles across the 10x10 board without detonating any mines. 

> *"No actual laptops or team members were detonated in the making of this project!"*