# cub3D

> *This project has been created as part of the 42 curriculum by nassaf and jboustan.*

A first-person 3D maze renderer written in C, inspired by Wolfenstein 3D (1992). The engine reads a 2D map from a file and renders it as a 3D scene using raycasting, with textured walls, coloured floor and ceiling, and free movement through the maze.

![cub3D demo](demo.gif)

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [How Raycasting Works](#how-raycasting-works)
- [Map Validation](#map-validation)
- [Debugging Notes](#debugging-notes)
- [Build and Run](#build-and-run)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Resources](#resources)
- [Use of AI](#use-of-ai)
- [Authors](#authors)

---

## Overview

The program reads a `.cub` scene file describing the map layout, the four wall textures (one per compass direction), and the floor and ceiling colours. It then opens a window and renders the maze from the player's point of view, redrawing every frame as the player moves.

Everything is written in C using miniLibX for window management and pixel drawing. No rendering library does the 3D work — the perspective is produced entirely by the raycasting maths described below.

This implementation covers the mandatory part of the subject. The bonus part was not attempted.

---

## Features

- **`.cub` parser** with validation of texture paths, RGB colour values, and map contents
- **Map validation** — closed by walls, exactly one player start, only legal characters
- **Textured raycasting** — a different texture depending on which face of the wall the ray struck
- **Floor and ceiling** filled with the colours defined in the scene file
- **Movement** — `W` `A` `S` `D` to walk and strafe, arrow keys to rotate
- **Clean exit** on `ESC` and on the window close button
- **No memory leaks, no crashes** — verified against a suite of deliberately malformed maps

---

## How Raycasting Works

For every frame, the renderer loops over each vertical column of the screen and casts one ray per column.

### Ray direction

The ray direction is computed by combining the player's forward vector with a scaled portion of the **camera plane** — a value running from `-1` at the left edge of the screen to `+1` at the right. This is what produces the field of view: each column gets a slightly different ray angle, fanning out across the player's view.

### Stepping through the grid (DDA)

The ray is advanced using the **DDA (Digital Differential Analysis)** algorithm, which steps through the 2D grid one cell boundary at a time, always advancing along whichever axis reaches the next grid line first.

This is the key property: DDA guarantees the ray never skips a wall, no matter how shallow or steep the angle. A naive fixed-step approach can step straight through a thin wall if the step size is larger than the wall is thick — DDA cannot, because it stops at every boundary crossing by construction.

### Correcting the fisheye

Once the DDA finds a wall, the engine computes the **perpendicular wall distance** — not the Euclidean distance from the player to the hit point, but that distance projected onto the camera plane.

This distinction matters. Using the raw Euclidean distance makes walls at the edges of the screen appear further away than those in the centre, bowing straight walls outward into a fisheye. Projecting onto the camera plane cancels the effect and keeps flat walls flat.

### Drawing the column

From the perpendicular distance the engine derives how tall the wall strip should be and which rows it occupies. The **texture column** is found by computing the exact fractional position where the ray struck the wall face, scaling it to the texture width, and flipping it where needed so the texture faces the correct direction. The **texture row** for each screen pixel is then mapped proportionally from that pixel's position within the strip.

### The pipeline

Each column passes through a chain of single-responsibility functions, carrying results forward in the `t_ray` struct:

```
init_ray → dda_setup → dda_run → get_wall_dist → get_tex
         → calc_draw_range → draw_ceiling_floor → draw_wall_strip
```

Ceiling and floor are filled with the flat colours from the `.cub` file, covering the rows above and below the wall strip — so every pixel in the column is written exactly once per frame.

---

## Map Validation

A map is only renderable if it is **fully enclosed by walls**. If any walkable cell is exposed to the outside, a ray can escape the grid entirely and the renderer has nothing to stop it.

Validation runs a **flood fill (BFS)** from the player's starting position, walking through every reachable `0` cell and checking all four neighbours. If any neighbour is a space rather than a wall, the map is rejected before the window ever opens.

### Why spaces matter

A space in the grid is **not** a wall — it represents emptiness. It can arrive two different ways:

| Source | How the space gets there |
|---|---|
| Written in the file | Trailing spaces typed directly into the `.cub` |
| Added by the parser | Rows shorter than the widest row are padded to match |

Both produce the same internal grid, so validation operates on the grid rather than the raw file. A `0` cell adjacent to a space in either case means that cell has no wall on that side — an open boundary — and the program exits with:

```
Error
Invalid Map - Open Boundary
```

---

## Debugging Notes

One bug is worth documenting, because the fix ended up being two-layered.

### The crash

On a map with an open boundary, a ray could walk off the edge of the grid. `dda_run` kept stepping, `map_y` kept incrementing, and eventually the ray read past the last row:

```
ray->map_y = 21
game->grid[21] = NULL          ← this row does not exist
game->grid[21][ray->map_x]     ← dereferencing NULL
                               → Segmentation fault
```

### The real fix

The flood fill in `flood1.c` catches the malformed map during validation and exits cleanly with an error message. If the map never passes validation, the renderer never runs on it — so the crash cannot occur.

### The safety net

A bounds check was also added at the top of the DDA loop, before any grid access:

```c
if (ray->map_x < 0 || ray->map_y < 0 || !game->grid[ray->map_y])
    break;
```

`game->grid` is an array of row pointers, so `!game->grid[map_y]` asks whether that row exists at all. A NULL row means the ray has walked off the bottom of the map, and the loop exits instead of dereferencing it.

This is defence in depth rather than the primary fix. If a malformed map ever slipped past validation, the renderer would produce broken visuals rather than a segfault — a bad frame is recoverable, a crash is not.

---

## Build and Run

### Requirements

Built and tested on Linux with the system X11 libraries. You will need `cc`, `make`, and the X11 development packages:

```bash
sudo apt install build-essential libx11-dev libxext-dev
```

### Compile

```bash
git clone https://github.com/josephboustany/cub3D.git
cd cub3D
make
```

The Makefile builds the bundled miniLibX in `minilibx-linux/` first, then the project sources. Available rules: `all`, `clean`, `fclean`, `re`.

### Run

The program takes one argument — the path to a `.cub` map:

```bash
./cub3D maps/good/subject_map.cub
```

Other maps to try:

```bash
./cub3D maps/good/library.cub
./cub3D maps/good/dungeon.cub
./cub3D maps/good/test_whitespace.cub
```

### Testing the parser

The maps in `maps/bad/` are broken on purpose. Each should exit with `Error` and a specific message rather than crashing:

```bash
./cub3D maps/bad/wall_hole_north.cub
./cub3D maps/bad/player_multiple.cub
./cub3D maps/bad/color_invalid_rgb.cub
```

---

## Controls

| Key | Action |
|---|---|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate view |
| `ESC` or window close | Quit |

---

## Project Structure

```
.
├── includes/            header
├── src/                 parsing, map validation, raycasting, mlx handling, utils
├── minilibx-linux/      miniLibX, compiled by the Makefile
├── maps/
│   ├── good/            valid maps
│   └── bad/             invalid maps for testing the parser
├── textures/new/        the four wall textures
├── Makefile
└── README.md
```

---

## Resources

- [Lode Vandevenne — Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference for this project; the camera plane, DDA and fisheye correction all follow from here
- 3DSage — *Make Your Own Raycaster* (YouTube) — useful for building an intuition before working through the maths
- [Permadi — Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) — a second explanation of the same concepts
- [Harm Smits — miniLibX guide](https://harm-smits.github.io/42docs/libs/minilibx) — for the mlx side
- The miniLibX man pages in `minilibx-linux/man/`
- `/usr/include/X11/keysymdef.h` — for key codes

---

## Use of AI

AI was used only to help understand the raycasting mathematics — questions such as why the camera plane is constructed the way it is, why perpendicular distance is used instead of Euclidean distance to avoid the fisheye effect, and for a clearer explanation of DDA stepping before working through Lode's tutorial.

It was not used to write the parser, the raycasting code, or anything else in `src/`. The code was written by us and we can explain every part of it.

---

## Authors

- **nassaf** — 42 Beirut · [github.com/nassaf338](https://github.com/nassaf338)
- **jboustan** — 42 Beirut · [github.com/josephboustany](https://github.com/josephboustany)

---

## License

This project is part of the 42 curriculum.
