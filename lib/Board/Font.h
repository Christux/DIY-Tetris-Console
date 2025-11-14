#include <avr/pgmspace.h>
#pragma once

/**
 * @brief 5x3 pixel representations of digits 0–9 stored in PROGMEM.
 *
 * Each digit is represented as a 5-row by 3-column matrix of bytes,
 * where 1 indicates a filled pixel and 0 indicates an empty pixel.
 * Storing in PROGMEM reduces RAM usage on AVR-based Arduinos.
 */
const static byte digits[10][5][3] PROGMEM = {
  {
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
  },
  {
    {0, 1, 0},
    {1, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {1, 1, 1},
  },
  {
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
  },
  {
    {1, 1, 1},
    {0, 0, 1},
    {0, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
  },
  {
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1},
  },
  {
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
  },
  {
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
  },
  {
    {1, 1, 1},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
  },
  {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
  },
  {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1},
  },
};
