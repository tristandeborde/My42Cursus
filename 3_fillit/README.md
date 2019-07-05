
# FILLIT

**Project Objectives :** Basic algorithms and parsing

## Intro

Fillit is a project about a recurring problem in programming: the search of an optimal solution among a very large number of possibilities, within a reasonable time. Here, we arrange Tetriminos between themselves to determine the smallest possible square that can accommodate them.

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

The implemented algorithm is a brute-force search that tests all solutions and returns the first one found.

For speed we used binary operations: instead of using a normal double table to store the tetriminos positions, we used a table of longs. Every block in a tetrimino corresponds to a set bit in the long, and an empty space to a 0.

In the case of a map of 5 by 5 we would have a `map = long[5]`
```
map:
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
00000111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
```

## Contributors

@pprikazs (Paul Prikazsky) student at 42
