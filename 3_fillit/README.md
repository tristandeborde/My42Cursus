
# FILLIT

**Project Objectives :** Basic algorithm, input/outputs

## Intro

Fillit is a project that allows you to discover and / or familiarize yourself with a recurrent problem in programming: the search of an optimal solution among a very large number of possibilities, within a reasonable time. In the case of this project, it will be a question of arranging Tetriminos between them and to determine the smallest possible square that can accommodate them.

## Usage

First, you have to `make`, then `./fillit [filename]`.

### Tetriminos set examples
```
....
....
####
....

....
..#.
..##
...#

....
....
#...
###.

....
.#..
.###
....
```
If you run the executable on the 4 tetriminos above, 
**result :**
```
AAAA.
B.C..
BBCCC
DB...
DDD..
```

### Project specificities

Th algorithm is a brute-force search that test all solutions and returns the first one found.

For speed we used binary operations.
Instead of using a normal double table to store information of the tetriminos positions we just used a table of long represented the tetriminos as 1 and empty space as 0.

In the case of a map of 5 by 5 we would have a `map = long[5]`
```
map:
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
```

This is much faster because of the speed of binary operation compared to memory access.

## Contributors

@blefeuvr (Baptiste Lefeuvre) student at 42
