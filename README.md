<img width="1020" height="506" alt="cub3d screenshot" src="https://github.com/user-attachments/assets/e8b152c9-0191-42f8-9685-9236469fff43" />

# cub3D

`cub3D` is a small raycasting game written in C with
[MLX42](https://github.com/codam-coding-college/MLX42). It renders a
Wolfenstein-style first-person view from a `.cub` map file, including textured
walls, floor and ceiling colors, a minimap, collision, mouse look, and
toggleable doors.

## Requirements

- `cc`
- `make`
- `cmake`
- `git`
- GLFW/OpenGL runtime dependencies required by MLX42

The first build clones MLX42 into `MLX42/` and builds it into `build/`, so it
needs network access the first time `make` is run.

## Build

```sh
make
```

Useful Makefile targets:

```sh
make clean    # remove object files
make fclean   # remove objects, binary, MLX42, and build directory
make re       # full rebuild
```

## Run

Map arguments are resolved relative to the `maps/` directory:

```sh
./cub3D [map]
```

For the included map:

```sh
./cub3D map.cub
```

## Controls

| Input | Action |
| --- | --- |
| `W` / `Up` | Move forward |
| `S` / `Down` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `Left` / `Right` | Turn camera |
| Mouse movement | Turn camera |
| `Enter` | Open or close the door in front of the player |
| Left mouse button | Open or close the door in front of the player |
| `Left Ctrl` | Toggle mouse capture |
| `Esc` | Quit |

## Map Format

A `.cub` file must contain six elements followed by a closed map:

```text
NO ./textures/Wall_1.png
EA ./textures/Wall_4_btorch.png
SO ./textures/Wall_2.png
WE ./textures/Wall_3_rtorch.png

F 13,30,13
C 0,0,0

111111
100001
10N0D1
111111
```

Elements:

- `NO`, `SO`, `WE`, `EA`: texture paths for north, south, west, and east walls
- `F`: floor RGB color, formatted as `R,G,B`
- `C`: ceiling RGB color, formatted as `R,G,B`

Map characters:

- `1`: wall
- `0`: empty floor
- `N`, `S`, `E`, `W`: player start position and orientation
- `D`: closed door

The map must be closed by walls. Invalid characters, missing elements,
incorrect RGB values, or leaks into spaces/out-of-bounds areas cause the program
to exit with an error.
