# DDA Bounds Check Fix — Explanation

## What is `dda_run`?

Every frame, for each vertical column of the screen, the game shoots a ray from the
player's position into the map. `dda_run` is the function that moves that ray one grid
cell at a time until it finds a wall (`'1'`). When it finds a wall, it stops — and the
game uses the distance to draw the wall on screen.

---

## The grid

`game->grid` is a 2D array of characters representing the map:

```
game->grid[0]  →  "111111111111"
game->grid[1]  →  "1N000000001 "
game->grid[2]  →  "111111111111"
...
game->grid[20] →  "111111111111"
game->grid[21] →  NULL           ← nothing here, the map ended
```

The ray uses `ray->map_y` as the row index and `ray->map_x` as the column index to
read a cell: `game->grid[ray->map_y][ray->map_x]`

---

## The problem — what happened without the fix

On a valid map, every ray always hits a `'1'` wall before leaving the grid. Fine.

On the **bad map** (open boundary), a ray could escape the grid entirely — there was no
wall to stop it. The loop kept running, `ray->map_y` kept increasing, and eventually:

```
ray->map_y = 21
game->grid[21] = NULL    ← this row does not exist

game->grid[ray->map_y][ray->map_x]
= game->grid[21][...]
= NULL[...]              ← reading from a NULL pointer
= Segmentation fault
```

The program crashed because it tried to read a memory address that does not exist.

---

## The fix

```c
if (ray->map_x < 0 || ray->map_y < 0
    || !game->grid[ray->map_y])
    break;
```

This runs **before** `game->grid[ray->map_y][ray->map_x]` is read.
It checks three things:

```
ray->map_x < 0              → ray walked off the LEFT side of the map
ray->map_y < 0              → ray walked off the TOP of the map
!game->grid[ray->map_y]     → this row is NULL → ray walked off the BOTTOM (or past the last row)
```

If any of these is true, `break` exits the loop immediately — no crash.

---

## Step by step on the bad map

```
Step 1: ray->map_y = 18  → game->grid[18] exists → keep going
Step 2: ray->map_y = 19  → game->grid[19] exists → keep going
Step 3: ray->map_y = 20  → game->grid[20] exists → keep going
Step 4: ray->map_y = 21  → game->grid[21] is NULL

WITHOUT fix:  reads NULL[x]  → Segmentation fault
WITH fix:     !game->grid[21] is true → break → exits cleanly
```

---

## What does `!game->grid[ray->map_y]` mean?

`game->grid` is an array of pointers. Each pointer points to one row string:

```
game->grid[0]  →  "111111111111"   ← valid pointer
game->grid[1]  →  "1N000000001 "   ← valid pointer
game->grid[2]  →  "111111111111"   ← valid pointer
game->grid[21] →  NULL             ← no row here, pointer is NULL
```

When the ray walks off the bottom of the map, `ray->map_y` becomes 21 (or past the
last row). At that point `game->grid[21]` is `NULL`.

In C, `NULL` is `0`, and `!0` is `true`. So:

```c
!game->grid[ray->map_y]
```

means: **"is this row NULL? does it NOT exist?"**

If yes → `break`.

Think of it like checking a shelf before grabbing a book:

```
shelf 0  →  book exists ✓
shelf 1  →  book exists ✓
shelf 21 →  empty shelf (NULL)

!game->grid[21]  →  "is this shelf empty?"  →  YES → don't reach, break
```

Without the check, the code tries to read from an empty shelf and crashes.

---

## Why this is a safety net, not the real fix

The flood fill fix in `flood1.c` is the **real fix** — it rejects the invalid map before
the game even starts. If the map is correctly rejected, `dda_run` never runs on it.

This bounds check is a **last line of defense**: if somehow a bad map slips past
validation, the renderer breaks out of the loop instead of segfaulting. The player would
see broken visuals rather than a crash.

Both fixes together:
- `flood1.c` → catches the bad map early, exits with a clear error message
- `raycast1.c` → prevents a crash if something ever slips through
