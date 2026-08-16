# Flood Fill Open Boundary Bug — Explanation

## The bad map row

Line 29 of `maps/good/cheese_maze_bad1.cub`:

```
1N00000000000000000000  
```

There are **2 explicit spaces at the end** of this row, written directly in the file.

---

## What the internal grid looks like

```
x:  0  1  2  3  4 ... 21 22 23
    1  N  0  0  0 ...  0  ' '' '
                       ^
              last '0' has a space to its right
```

The flood fill BFS starts at `N` (x=1) and walks through all the `0`s to the right.
It eventually reaches the last `0` at x=21, then calls `check_right` to look at x=22 — which is `' '`.

**That space is not a wall.** The `0` at x=21 has no wall protecting its right side — it is an open boundary.

---

## Old code vs. new code

| | What happens when `check_right` sees `' '` at x=22 |
|---|---|
| **Old code** | `return(0)` — treated like a wall, no error raised |
| **New code** | `free_exit2("Invalid Map - Open Boundary")` — exits cleanly |

### Old behavior (broken)
```
flood fill reaches '0' at x=21
    → check_right reads ' ' at x=22
    → returns 0 (silent, no error)
    → flood fill thinks the map is closed
    → validation passes
    → game launches
    → DDA ray hits grid out of bounds
    → Segmentation fault
```

### New behavior (fixed)
```
flood fill reaches '0' at x=21
    → check_right reads ' ' at x=22
    → free_exit2("Invalid Map - Open Boundary")
    → program exits cleanly with: Error\nInvalid Map - Open Boundary
```

---

## The fix in `src/flood1.c`

Added in each of `check_up`, `check_down`, `check_left`, `check_right`:

```c
if (c == ' ')
    free_exit2(map_data, map_check, "Invalid Map - Open Boundary");
```

This is placed **before** the original validity check, so a space adjacent to any walkable `'0'` cell is immediately caught as an open boundary.

---

## Key takeaway

A `' '` (space) in the map grid is not a wall. It represents emptiness — either explicit trailing spaces written in the `.cub` file, or padding added by the parser when rows have different lengths. Either way, a `'0'` cell touching a space means that cell has no wall on that side, which is an open boundary. The fix makes the flood fill treat it as such.

---

## What if the spaces are removed from line 29?

Suppose you strip the trailing spaces from line 29, so the file now contains:

```
1N00000000000000000000       ← 22 chars, no trailing spaces
```

The fix still catches the open boundary. Here is why.

Nearly every other row in the file still has 2 trailing spaces:

```
1111111111111111111111  ← 22 chars + 2 spaces = 24 chars
1001000001000000000001  ← 22 chars + 2 spaces = 24 chars
...
```

The parser determines `map_data->width` from the **longest row it finds**, which is 24. It then pads every shorter row with spaces to reach that width. Line 29 (22 chars) gets 2 spaces added automatically:

```
File on disk:   1N00000000000000000000        (22 chars, no spaces written)
                        ↓
Parser pads to width=24:
Internal grid:  1N00000000000000000000[' '][' ']
```

The internal grid is **identical** to when the spaces were explicit. The last `0` at x=21 is still adjacent to `' '` at x=22. The flood fill hits that space, the fix fires, and the program exits with `Error\nInvalid Map - Open Boundary`.

### Two sources, same result

| Situation | What puts `' '` at x=22 | Fix catches it? |
|---|---|---|
| Spaces written explicitly in the file | The file itself | Yes |
| Spaces removed from the file | Parser pads the shorter row to match width | Yes |

The fix operates on the **internal grid**, not the raw file. As long as any other row is wider than line 29, the parser will pad line 29 and the space will still be there. The only real fix for the map itself is to end the `0`s with a `1` (a real wall), so no `0` is ever adjacent to a space.
