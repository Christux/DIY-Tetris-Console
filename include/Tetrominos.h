#include <avr/pgmspace.h>
#pragma once

/**
 * @brief Tetromino shapes for Tetris, stored in program memory.
 *
 * Each tetromino is represented as a set of 4 block coordinates (X and Y)
 * for each rotation. Stored in PROGMEM to save RAM on AVR-based Arduinos.
 *
 * The commented grids show the visual shape in a 4x4 representation:
 * '.' = empty, '#' = filled
 */
PROGMEM constexpr static byte tetrominos[19][2][4] = {
  // I
  {
    // Rotation 0
    // ....
    // ....
    // ####
    // ....
    { 0, 1, 2, 3 },  // X
    { 2, 2, 2, 2 },  // Y
  },
  {
    // Rotation 1
    // ..#.
    // ..#.
    // ..#.
    // ..#.
    { 2, 2, 2, 2 },
    { 0, 1, 2, 3 },
  },
  // O
  {
    // Rotation 0 (only rotation)
    // ....
    // .##.
    // .##.
    // ....
    { 1, 1, 2, 2 },
    { 1, 2, 1, 2 },
  },
  // J
  {
    // Rotation 0
    // ...
    // ###
    // ..#
    { 0, 1, 2, 2 },
    { 1, 1, 1, 2 },
  },
  {
    // Rotation 1
    // .#.
    // .#.
    // ##.
    { 1, 1, 0, 1 },
    { 0, 1, 2, 2 },
  },
  {
    // Rotation 2
    // #..
    // ###
    // ...
    { 0, 0, 1, 2 },
    { 0, 1, 1, 1 },
  },
  {
    // Rotation 3
    // .##
    // .#.
    // .#.
    { 1, 2, 1, 1 },
    { 0, 0, 1, 2 },
  },
  // L
  {
    // Rotation 0
    // ...
    // ###
    // #..
    { 0, 1, 2, 0 },
    { 1, 1, 1, 2 },
  },
  {
    // Rotation 1
    // ##.
    // .#.
    // .#.
    { 0, 1, 1, 1 },
    { 0, 0, 1, 2 },
  },
  {
    // Rotation 2
    // ..#
    // ###
    // ...
    { 2, 0, 1, 2 },
    { 0, 1, 1, 1 },
  },
  {
    // Rotation 3
    // .#.
    // .#.
    // .##
    { 1, 1, 1, 2 },
    { 0, 1, 2, 2 },
  },
  // S
  {
    // Rotation 0
    // ...
    // .##
    // ##.
    { 1, 2, 0, 1 },
    { 1, 1, 2, 2 },
  },
  {
    // Rotation 1
    // #..
    // ##.
    // .#.
    { 0, 0, 1, 1 },
    { 0, 1, 1, 2 },
  },
  // Z
  {
    // Rotation 0
    // ...
    // ##.
    // .##
    { 0, 1, 1, 2 },
    { 1, 1, 2, 2 },
  },
  {
    // Rotation 1
    // .#.
    // ##.
    // #..
    { 1, 0, 1, 0 },
    { 0, 1, 1, 2 },
  },
  // T
  {
    // Rotation 0
    // ...
    // ###
    // .#.
    { 0, 1, 2, 1 },
    { 1, 1, 1, 2 },
  },
  {
    // Rotation 1
    // .#.
    // ##.
    // .#.
    { 1, 0, 1, 1 },
    { 0, 1, 1, 2 },
  },
  {
    // Rotation 2
    // .#.
    // ###
    // ...
    { 1, 0, 1, 2 },
    { 0, 1, 1, 1 },
  },
  {
    // Rotation 3
    // .#.
    // .##
    // .#.
    { 1, 1, 2, 1 },
    { 0, 1, 1, 2 },
  }
};

/**
 * @brief Maximum rotation count for each tetromino type (I, O, J, L, S, Z, T)
 */
const uint8_t tetrominosMaxRotation[7] = { 2, 1, 4, 4, 2, 2, 4 };

/**
 * @brief Indexes of the first rotation for each tetromino type in `tetrominos`.
 */
const uint8_t tetrominosIndexes[7] = { 0, 2, 3, 7, 11, 13, 15 };

/**
 * @brief Internal textures for each tetromino type (3x3 matrix), stored in PROGMEM.
 *
 * Each texture represents the visual appearance of a tetromino in a 3x3 grid:
 * '.' = empty, '#' = filled
 */
PROGMEM constexpr byte internalBricTextures[7][3][3] = {
  // I
  {
    // ###
    // ###
    // ###
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  },
  // O
  {
    // ...
    // ...
    // ...
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  // J
  {
    // #..
    // ##.
    // ###
    {1, 0, 0},
    {1, 1, 0},
    {1, 1, 1}
  },
  // L
  {
    // .##
    // ..#
    // ...
    {0, 1, 1},
    {0, 0, 1},
    {0, 0, 0}
  },
  // S
  {
    // .#.
    // #.#
    // .#.
    {0, 1, 0},
    {1, 0, 1},
    {0, 1, 0}
  },
  // Z
  {
    // ###
    // #.#
    // ###
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  // T
  {
    // ...
    // .#.
    // ...
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 0}
  }
};

/**
 * @brief Miniature representation of tetrominos for "next piece" display.
 *
 * Each tetromino is represented as an 8x8 grid for small previews.
 * Stored in PROGMEM to save RAM.
 *
 * Visual representation in comments:
 * '.' = empty, '#' = filled
 */
PROGMEM constexpr static byte miniTetrominos[7][4][8] = {
  // I
  {
    // ........
    // ########
    // ########
    // ........
    { 0,0,0,0,0,0,0,0 },
    { 1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1 },
    { 0,0,0,0,0,0,0,0 },
  },
  // O
  {
    // ..####..
    // ..####..
    // ..####..
    // ..####..
    { 0,0,1,1,1,1,0,0 },
    { 0,0,1,1,1,1,0,0 },
    { 0,0,1,1,1,1,0,0 },
    { 0,0,1,1,1,1,0,0 },
  },
  // J
  {
    // .##.....
    // .##.....
    // .####### 
    // .####### 
    { 0,1,1,0,0,0,0,0 },
    { 0,1,1,0,0,0,0,0 },
    { 0,1,1,1,1,1,1,0 },
    { 0,1,1,1,1,1,1,0 },
  },
  // L
  {
    // .....##.
    // .....##.
    // .######.
    // .######.
    { 0,0,0,0,0,1,1,0 },
    { 0,0,0,0,0,1,1,0 },
    { 0,1,1,1,1,1,1,0 },
    { 0,1,1,1,1,1,1,0 },
  },
  // S
  {
    // ...####.
    // ...####.
    // .####...
    // .####...
    { 0,0,0,1,1,1,1,0 },
    { 0,0,0,1,1,1,1,0 },
    { 0,1,1,1,1,0,0,0 },
    { 0,1,1,1,1,0,0,0 },
  },
  // Z
  {
    // .####...
    // .####...
    // ...####.
    // ...####.
    { 0,1,1,1,1,0,0,0 },
    { 0,1,1,1,1,0,0,0 },
    { 0,0,0,1,1,1,1,0 },
    { 0,0,0,1,1,1,1,0 },
  },
  // T
  {
    // ...##...
    // ...##...
    // .######.
    // .######.
    { 0,0,0,1,1,0,0,0 },
    { 0,0,0,1,1,0,0,0 },
    { 0,1,1,1,1,1,1,0 },
    { 0,1,1,1,1,1,1,0 },
  },
};