#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SH110X.h>
#include "FourBitsTable.h"
#include "Board.h"
#include "Font.h"
#include "Tetrominos.h"

#ifdef SSD1306
Board::Board(Adafruit_SSD1306* display)
  : _xoffset(2),
    _yoffset(7),
    _display(display) {}
#else
Board::Board(Adafruit_SH1106G* display)
  : _xoffset(2),
    _yoffset(7),
    _display(display) {}
#endif

void Board::setup() {
  // Nothing to do
}

void Board::clear() {
  _display->clearDisplay();
}

void Board::commit() {
  _display->display();
}

void Board::drawBackground() const {

  _display->drawFastVLine(0, 0, 127, WHITE);
  _display->drawFastVLine(62, 0, 127, WHITE);
  _display->drawFastHLine(0, 127, 63, WHITE);

  _display->drawFastVLine(37, 0, 5, WHITE);
  _display->drawFastVLine(49, 0, 5, WHITE);

  _display->drawFastHLine(0, 5, 5, WHITE);
  _display->drawFastHLine(35, 5, 5, WHITE);
  _display->drawFastHLine(47, 5, 5, WHITE);
}

long Board::power10(uint8_t n) const {
  long result = 1;
  while (n--) {
    result *= 10;
  }
  return result;
}

void Board::drawNumber(long n, uint8_t d, uint8_t o) {
  long p = power10(d - 1);

  for (uint8_t i = 0; i < d; i++) {
    const long digit = n / p;
    drawDigit(i * 4 + o, 0, digit);
    n -= digit * p;
    p /= 10;
  }
}

void Board::drawDigit(uint8_t x, uint8_t y, uint8_t digit) {
  for (uint8_t i = 0; i < 5; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      if (pgm_read_byte(&digits[digit][i][j])) {
        _display->drawPixel(x + j, y + i, WHITE);
      }
    }
  }
}

void Board::drawScore(long score) {
  drawNumber(score, ScoreDigits, 4);
}

void Board::drawLevel(uint8_t level) {
  drawNumber(level, 2, 40);
}

void Board::drawBric(char y, char x, uint8_t m, uint8_t n, uint8_t nHidden, uint8_t type) {
  if (y < m && y >= nHidden && x < n && x >= 0) {
    //_display->fillRect(_xoffset + ((5 + 1)) * x, _yoffset + ((5 + 1)) * (y - nHidden), 5, 5, WHITE);
    _display->drawRect(
      _xoffset + (BlockSize + BlockSpacing) * x,
      _yoffset + (BlockSize + BlockSpacing) * (y - nHidden),
      BlockSize,
      BlockSize,
      WHITE
    );

    for (uint8_t i = 0; i < 3; i++) {
      for (uint8_t j = 0; j < 3; j++) {
        if (pgm_read_byte(&internalBricTextures[type][i][j])) {
          _display->drawPixel(
            i + _xoffset + (BlockSize + BlockSpacing) * x + 1,
            j +  _yoffset + (BlockSize + BlockSpacing) * (y - nHidden) + 1,
            WHITE
          );
        }
      }
    }
  }
}

void Board::drawNextTetromino(uint8_t type) {
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      if (pgm_read_byte(&miniTetrominos[type][i][j])) {
        _display->drawPixel(j + 52, i, WHITE);
      }
    }
  }
}

void Board::drawBlocs(FourBitsTable* grid, uint8_t m, uint8_t n, uint8_t nHidden) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      //Serial.println(a[i * n + j]);
      uint8_t element = grid->get(i * n + j);
      if (element > 0) {
        drawBric(i, j, m, n, nHidden, element - 1);
      }
    }
  }
}

void Board::drawTetromino(char y, char x, uint8_t m, uint8_t n, uint8_t nHidden, uint8_t type, uint8_t rotation) {
  for (uint8_t i = 0; i < 4; i++) {
    drawBric(
      y + (uint8_t)pgm_read_byte(&tetrominos[tetrominosIndexes[type] + rotation][1][i]),
      x + (uint8_t)pgm_read_byte(&tetrominos[tetrominosIndexes[type] + rotation][0][i]),
      m,
      n,
      nHidden,
      type
    );
  }
}