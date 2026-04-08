# Langton's Ant

A simulator based on Langton's Ant, extended with an ant colony featuring multiple ant types, reproduction, and emergent behavior.

![Langton's Ant](langton.png)

## What is Langton's Ant?

Langton's Ant is a two-dimensional agent that moves on a grid of cells following two simple rules:

- On a white cell: turn right, flip the cell to black, move forward.
- On a black cell: turn left, flip the cell to white, move forward.

Despite the simplicity of these rules, complex and unpredictable patterns emerge over time.

## Ant types

| Type | Role |
|------|------|
| Worker | Basic ant following the Langton algorithm |
| Queen | Reproduces when it encounters a Breeder |
| Breeder | Triggers reproduction in Queens |
| Soldier | Non-reproductive ant |

Queens spawn offspring with the following probability distribution: 1% Queen, 55% Worker, 9% Breeder, 35% Soldier. All ants die after reaching a maximum age.

## Controls

| Key | Action |
|-----|--------|
| Enter | Clear the grid and spawn a new random population |
| Space | Pause / resume the simulation |
| Tab | Advance one step (while paused) |
| Right arrow | Increase simulation speed |
| Left arrow | Decrease simulation speed |
| Up arrow | Increase spawn probability |
| Down arrow | Decrease spawn probability |
| Esc | Exit |

| Mouse button | Action |
|--------------|--------|
| Left click | Create a Worker ant, or rotate an existing ant |
| Right click | Cycle the ant type at that cell (Worker -> Queen -> Breeder -> Soldier) |
| Middle click | Delete the ant at that cell |

## Building

### Requirements

- C++11 or later
- [SFML 2.x](https://www.sfml-dev.org/) installed at `C:/SFML`
- MinGW (GCC)
- CMake 3.25 or later

### Compile

```bash
cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/mingw64/bin/c++.exe
cmake --build build
```

The executable is generated inside the `build/` directory. Run it from there so that the relative paths to `assets/` resolve correctly.

## Project structure

```
Langton/
├── src/          Source files
├── include/      Header files
├── assets/       Images and font
└── CMakeLists.txt
```
