# Tower Defend

An automated tower-defense simulation written in C99 with SDL2. A procedurally generated horde (dragons, archers, knights, gargoyles) marches along a path to destroy the King's tower, while the defending towers are placed automatically by a scoring algorithm.

Team project, 2nd year BSc Computer Science (L2), University of Poitiers, *C Programming* course, 2025–26.

https://github.com/user-attachments/assets/e1a622a4-c45f-4175-838b-60dfd6e356ef

## How it works

- **Two factions:** the King (ground towers, air towers, the King's tower) against the Horde (archers, knights, dragons, gargoyles). Each unit has its own hit points, damage, range, attack speed, and target type (ground, air, or both).
- **Procedural generation:** the attack path is a constrained random walk from the bottom of the board, regenerated if it gets stuck (`initChemin`), and the horde's spawns are randomized every turn.
- **Automatic tower placement:** each free cell is scored by its Manhattan distance to every cell of the path (`calculScore`), and new towers go on the highest-scoring cell (`placementAutoTour`).
- **Turn-based combat:** each turn, units move along the path, find the targets in range (`quiEstAPortee`), and attack once (`resoudreCombats`). The game ends when the King's tower falls.

## Technical highlights

- **Data structures:** each player is a singly linked list of units (`TListePlayer`), and the board is a dynamically allocated 2D array of unit pointers (`TplateauJeu`).
- **Memory management:** explicit `malloc`/`free` for every unit, list cell, and the path array, including removing destroyed units from lists.
- **Persistence:** save and load a running game in two formats: a binary file (`fwrite`/`fread`) and a human-readable sequential text file.
- **Rendering:** 2D sprite rendering with SDL2 surfaces.

## Build and run

Requirements: a C compiler and SDL2 (`libsdl2-dev` on Debian/Ubuntu, `brew install sdl2` on macOS, `mingw-w64-x86_64-SDL2` in MSYS2 on Windows).

```bash
make
./towerdefend
```

Run it from the repository root, since sprites are loaded from `./data/`.

### Controls

| Key | Action |
|---|---|
| `S` | Save the game (binary, `partiebin.clb`) |
| `D` | Save the game (text, `partieseq.cls`) |
| `C` | Load the binary save |
| `V` | Load the text save |
| `Esc` | Quit |

## Repository layout

```
src/     Game logic (towerdefend.c), entry point (main.c), SDL rendering helpers (maSDL.c)
data/    Sprites
docs/    Assignment, course notes and a demo video (in French)
```

`maSDL.c`, the `main.c` skeleton and the tower-creation helpers were provided by the course. The game core (movement, targeting, combat, automatic tower placement, save/load) is the team's work.
