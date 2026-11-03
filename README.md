*This project has been created as part of the 42 curriculum by aabdella, pecastro.*

# miniRT

> My first RayTracer with miniLibX: a small ray tracer written in C.

![tree scene](example_scenes/tree.png)

---

## Description

**miniRT** turns a text file that describes a 3D scene into an image. For every
pixel of the window it shoots a ray from the camera into the scene, finds the
closest object the ray hits, and works out the colour of that point from the
lights, the surface normal and whether something else is blocking the light.

The goal of the project is to learn the maths behind computer graphics from
the ground up: **vectors and points** (tuples), **4×4 matrices** (translation,
scaling, rotation, inversion), **ray–object intersection** (solving quadratics),
and a **lighting model** (Phong reflection with hard shadows). Our main reference
was *The Ray Tracer Challenge* by Jamis Buck, and the design follows it closely.

### Features at a glance

| Area | What is supported |
|---|---|
| **Objects** | Sphere `sp`, plane `pl`, finite cylinder with caps `cy` |
| **Transformations** | Every object has its own 4×4 transform: position, orientation (any unit vector) and size |
| **Camera** | Any position, any view direction, horizontal field of view 0–180° |
| **Lighting** | Ambient + diffuse + specular (Phong), **hard shadows** |
| **Multiple lights** | Any number of `L` lines; the lighting from each one is added up |
| **Coloured light** | Ambient and spot lights carry an RGB colour that tints the result |
| **Inside objects** | Normals are flipped when the camera is inside an object, so interiors are lit correctly |
| **Window** | 1440 × 900, `ESC` or the window's close button exits cleanly |
| **Parsing** | Strict validation of every value, with an `Error\n<reason>` message |

---

## Instructions

### Requirements

- Linux with an X server (developed and tested on Ubuntu / WSL2 with WSLg)
- `cc` (gcc or clang), `make`
- X11 development headers and zlib (used by MiniLibX)

```bash
# Debian / Ubuntu
sudo apt install build-essential libx11-dev libxext-dev zlib1g-dev
```

### Build

MiniLibX is included in [minilibx-linux/](minilibx-linux/) but the default `make`
does **not** build it, so on a fresh clone build it once first:

```bash
make minilibx   # builds minilibx-linux/libmlx.a (only needed once)
make            # builds libft, then ./miniRT
make clean      # removes object files
make fclean     # removes object files, libft.a and the binary
make re         # fclean + all
make debug      # rebuild with -g
```

Compiled with `-Wall -Wextra -Werror`, linked with `-lmlx -lX11 -lXext -lm -lz`.

### Run

```bash
./miniRT scene/tree.rt
```

The program takes **exactly one** argument, a file ending in `.rt`. It renders the
scene once, shows it in a window and waits. Press **`ESC`** or close the window to
quit; all memory and MiniLibX resources are freed on exit.

### Quick demo

A minimal scene, `demo.rt`:

```
A   0.2                    255,255,255
C   0,0,-20   0,0,1   70
L   -10,10,-20   0.8       255,255,255

pl  0,-3,0     0,1,0       200,200,200
sp  0,0,0      6           255,0,0
cy  6,0,2      0,1,0   3   6   10,0,255
```

```bash
./miniRT demo.rt      # opens a window with a red sphere and a blue cylinder on a grey floor
./miniRT demo.txt
Error
file format <filename>.rt
```

---

## Scene file format (`.rt`)

One element per line. Fields are separated by **spaces**, vector/colour
components by **commas**. Empty lines are ignored; elements can appear in any
order.

| Id | Element | Fields | Example |
|---|---|---|---|
| `A` | Ambient light | ratio `[0,1]`, RGB | `A 0.2 255,255,255` |
| `C` | Camera | position, **unit** view direction, FOV `[0,180]` | `C -50,0,20 0,0,1 70` |
| `L` | Light | position, brightness `[0,1]`, RGB | `L -40,0,30 0.7 255,255,255` |
| `sp` | Sphere | centre, diameter, RGB | `sp 0,0,20 20 255,0,0` |
| `pl` | Plane | point, **unit** normal, RGB | `pl 0,-20,0 0,1,0 255,0,225` |
| `cy` | Cylinder | centre, **unit** axis, diameter, height, RGB | `cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255` |

Rules the parser enforces:

- Exactly **one** `A` and **one** `C`; at least one `L` and at least one object.
- Direction vectors must be normalised (length 1 within `1e-5`).
- RGB components are integers in `0–255`; sizes must not be negative.
- Only `.rt` files, and hidden files (starting with `.`) are rejected.
- Any problem prints `Error\n` followed by the reason on stderr, and the program
  exits without opening a window.

---

## Architecture

### The big picture

```
   scene.rt
      │
      ▼
 ┌──────────────────────────────────────────────┐
 │                  parse_input                 │
 │  1. read lines (get_next_line), skip blanks  │
 │  2. split on ' ', dispatch on identifier     │
 │  3. validate every field                     │
 │  4. build transform + inverse per object     │
 │  5. check required elements (A, C, L, obj)   │
 └──────────────────────┬───────────────────────┘
                        │ t_world (objects, lights, ambient, camera)
                        ▼
 ┌──────────────────────────────────────────────┐
 │                  render_loop                 │
 │  for each pixel (x, y):                      │
 │    ray_for_pixel      camera → world ray     │
 │    intersect_world    all hits, sorted by t  │
 │    check_if_hit       closest t > EPSILON    │
 │    prepare_computations  point, eye, normal  │
 │    shade_hit          ambient + Σ lights     │
 │      is_shadowed      ray from point to light│
 │    img_pix_put        write into mlx image   │
 │  mlx_put_image_to_window, then mlx_loop      │
 └──────────────────────────────────────────────┘
```

`main()` only checks the argument, parses the scene, sets up MiniLibX, renders
once and hands control to `mlx_loop`.

### Source map

| File | Responsibility |
|---|---|
| [src/main.c](src/main.c) | Argument check, parse → setup → render → `mlx_loop` |
| [parsing/parsing.c](parsing/parsing.c) | Reads the file, dispatches each line by identifier |
| [parsing/parse_*.c](parsing/) | One parser per element (`A`, `C`, `L`, `sp`, `pl`, `cy`); builds its transform |
| [parsing/parsing_utils*.c](parsing/) | Error output, `.rt` check, number / RGB / unit vector validation, `align_to_vec` rotation |
| [parsing/free_scene.c](parsing/free_scene.c) | Frees the whole `t_world` |
| [src/construct_tuples.c](src/construct_tuples.c), [src/utils_tuple.c](src/utils_tuple.c) | Points / vectors: add, subtract, dot, cross, normalise, scale |
| [src/construct_matrix.c](src/construct_matrix.c), [src/inversion_matrix.c](src/inversion_matrix.c) | Identity, transpose, determinant, cofactors, inverse |
| [src/transform_matrix.c](src/transform_matrix.c), [src/transform_tuple.c](src/transform_tuple.c) | Translation, scaling, rotation matrices; matrix × tuple |
| [src/implement_camera.c](src/implement_camera.c) | `view_transform`, pixel size from FOV and aspect ratio |
| [src/ray_for_pixel.c](src/ray_for_pixel.c) | The ray through the centre of a given pixel |
| [src/intersections.c](src/intersections.c) | Ray into object space, intersect every object, sort hits |
| [src/intersect_objects.c](src/intersect_objects.c) | Sphere, plane and cylinder intersection |
| [src/intersect_cylinder_utils.c](src/intersect_cylinder_utils.c) | Cylinder height truncation and end caps |
| [src/computations.c](src/computations.c) | Hit point, eye vector, surface normal (incl. inside flip) |
| [src/lighting.c](src/lighting.c), [src/lighting2.c](src/lighting2.c) | Ambient, Phong diffuse + specular, shadow test |
| [src/render_loop.c](src/render_loop.c) | Per‑pixel loop, `color_at`, closest hit |
| [src/minilibx.c](src/minilibx.c) | Window / image setup, pixel writes, key and close hooks, `terminate` |
| [lib/Libft_all/](lib/Libft_all/) | Our libft (+ `get_next_line`, `ft_atof`, …) |

### 1. Every object is a unit shape plus a matrix

Intersection code only knows **one** shape of each kind, centred at the origin:

| Object | Shape in object space |
|---|---|
| Sphere | radius 1 around the origin |
| Plane | the plane `y = 0`, normal `(0, 1, 0)` |
| Cylinder | radius 1 around the y axis, cut at `±height/2`, with closed caps |

The parser turns the values in the `.rt` file into a 4×4 **transform** that
moves that unit shape into the world:

```
sphere   : T = translate(centre) · scale(d/2, d/2, d/2)
plane    : T = translate(point) · rotate(+Y → normal)
cylinder : T = translate(centre) · rotate(+Y → axis) · scale(d/2, h/2, d/2)
```

`rotate(+Y → v)` is built in `align_to_vec()` with Rodrigues' formula: rotate
around `Y × v` by the angle `acos(Y · v)`. The **inverse** of each transform is
computed once while parsing and stored in the object, so it is never
recomputed while rendering.

To intersect, the ray is moved into object space with the inverse
(`transform_ray`) and tested against the unit shape. Normals go back to world
space with the **transposed inverse**, which keeps them perpendicular even when
the object is scaled unevenly.

### 2. Camera and rays

`view_transform(from, to, up)` builds the camera matrix from the position and
direction in the `C` line. The up vector is `(0, 1, 0)`, or `(0, 0, 1)` when the
camera looks straight up or down (otherwise the cross product would be zero).

From the field of view and the window's aspect ratio, `pixel_size()` computes
how wide one pixel is on a canvas one unit in front of the camera.
`ray_for_pixel()` takes the centre of pixel `(x, y)` on that canvas, moves it
and the origin with the camera's inverse, and the ray is the normalised
direction between them.

### 3. Intersections

- **Sphere**: solve `|O + tD|² = 1`, a quadratic, giving 0 or 2 values of `t`.
- **Plane**: `t = -O.y / D.y`; no hit if the ray is parallel (`|D.y| < EPSILON`).
- **Cylinder**: solve `x² + z² = 1` for the side, drop hits outside
  `±height/2` (`truncate_cylinder`), then test both caps (`intersection_caps`).

All hits of all objects go into one array, which is sorted by `t`. The **hit**
is the first one with `t > EPSILON`: anything behind the camera, or too close to
the ray's origin, is ignored.

### 4. Shading

`prepare_computations()` collects what the lighting needs: the hit point, the
eye vector (towards the camera) and the normal. If the normal points away from
the eye, we are **inside** the object and the normal is flipped.

`shade_hit()` then adds up:

```
colour = object_colour · ambient_rgb · ambient_ratio · k_ambient
       + Σ over lights:
           shadowed? → ambient part only
           else      → ambient + diffuse (L·N) + specular (R·E)^shininess
```

| Material constant | Sphere / Cylinder | Plane |
|---|---|---|
| ambient | 0.1 | 0.1 |
| diffuse | 0.7 | 0.7 |
| specular | 0.7 | 0.0 (matte floor and walls) |
| shininess | 200 | 200 |

**Shadows**: `is_shadowed()` casts a ray from the hit point towards the light.
If something is hit before the light (`EPSILON < t < distance`), the point is
in shadow. The `EPSILON` threshold stops a surface from shadowing itself
("shadow acne").

Colours are kept as doubles in `[0, 1]` during the whole computation and only
clamped and packed to `0xRRGGBB` in `color_to_int()` right before the pixel is
written.

---

## Error messages

| Situation | Message (after `Error\n`) |
|---|---|
| Not exactly one argument | `enter one argument only` |
| Wrong extension | `file format <filename>.rt` |
| Hidden file | `Hidden files are not allowed` |
| Empty file | `empty file` |
| Unknown identifier, or tabs between fields | `wrong or missing identifier` |
| Missing `A` / `C` / `L` / objects | `missing ambient light`, `missing camera`, … |
| Second `A` or `C` | `repeated ambient`, `repeated camera` |
| Direction not of length 1 | `vector is not normalized` |
| Colour out of range | `RGB out of range (0-255)` |
| FOV, ratio or brightness out of range | `field of view out of range`, … |

---

## Testing

The [scene/](scene/) folder holds the scenes we used while developing:

| Path | What it shows |
|---|---|
| [scene/sphere.rt](scene/sphere.rt), [scene/cylinder.rt](scene/cylinder.rt) | One object, to check shape, size and normals |
| [scene/spheres*.rt](scene/), [scene/whitespheres.rt](scene/whitespheres.rt) | Several objects, overlapping shadows |
| [scene/intersection.rt](scene/intersection.rt) | Objects cutting through each other |
| [scene/inside.rt](scene/inside.rt) | Camera inside an object |
| [scene/camera/view1–8.rt](scene/camera/) | The same scene seen from 8 directions (incl. straight up / down) |
| [scene/tree.rt](scene/tree.rt), [scene/wall_e.rt](scene/wall_e.rt), [scene/Dan_flavin.rt](scene/Dan_flavin.rt), … | Bigger compositions with many objects and rotated cylinders |
| [scene/invalid/](scene/invalid/) | ~30 broken files, one for each parser error |

Check all the invalid files at once (none of them should open a window):

```bash
for f in scene/invalid/*; do echo "== $f"; ./miniRT "$f"; done
```

Memory checks with valgrind (close the window with `ESC` when it has rendered):

```bash
make debug
valgrind --leak-check=full --show-leak-kinds=all ./miniRT scene/sphere.rt
```

---

## Evaluation walkthrough

A suggested order for showing the project:

1. **Build**: `make minilibx && make` (no relink on a second `make`), norminette on `src/`, `parsing/`, `include/`.
2. **Arguments**: no argument, two arguments, a `.txt` file, a hidden file, a missing file.
3. **Invalid scenes**: run the loop over [scene/invalid/](scene/invalid/) above.
4. **Each object**: [scene/sphere.rt](scene/sphere.rt), a plane, [scene/cylinder.rt](scene/cylinder.rt) (sides and caps).
5. **Transformations**: change positions, diameters and axis vectors in a scene file and re‑run.
6. **Camera**: [scene/camera/](scene/camera/) views, and a FOV change.
7. **Light**: move the `L`, change brightness, show shadows and the specular spot on spheres.
8. **Inside an object**: [scene/inside.rt](scene/inside.rt).
9. **Window**: `ESC`, the close button, minimise and restore (the image stays).
10. **Leaks**: run the valgrind command above.

---

## Resources

### References

- Jamis Buck, *The Ray Tracer Challenge*, Pragmatic Bookshelf (2019): our main
  reference for tuples, matrices, transformations, the camera, intersections and
  Phong shading.
- [MiniLibX documentation (42 Docs)](https://harm-smits.github.io/42docs/libs/minilibx): windows, images and event hooks.
- [Scratchapixel: ray–sphere, ray–plane and ray–cylinder intersection](https://www.scratchapixel.com/)
- [Rodrigues' rotation formula](https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula), used to orient planes and cylinders.
- [Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model)
- Linux man pages: `open(2)`, `read(2)`, `malloc(3)`, `math.h` (`sqrt`, `pow`, `tan`, `acos`).

### Use of AI

AI assistants were used as a support tool, never as a replacement for
understanding the code:

- **Explanations**: clarifying ray tracing concepts (view transform, normals and
  the transposed inverse, shadow acne) and C patterns such as memory management
  and splitting functions to fit the Norm.
- **Documentation**: drafting and structuring this README from the existing code.

No AI was used to write the core ray tracing algorithms or to create the `.rt`
scene files; all implementation logic was written and reviewed by us.
