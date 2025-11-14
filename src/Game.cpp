#include "HardwareSerial.h"
#include <Arduino.h>
#include "Config.h"
#include "FourBitsTable.h"
#include "Game.h"

Game::Game(Board* board, FourBitsTable* grid)
  : _board(board),
    _nHidden(GRID_HIDDEN_ROWS),
    _m(GRID_HEIGHT),
    _n(GRID_WIDTH),
    _grid(grid),
    _running(false),
    _delay(150),
    _nextFlicker(0),
    _delayY(1000),
    _nextFlickerY(0) {
}

void Game::setup() {
  _board->setup();
}

void Game::handle() {
  long curr_time = millis();

  // Tetromino falling
  if (_running && curr_time >= _nextFlickerY) {
    _nextFlickerY = curr_time + _delayY;
    incraseY();
  }

  // Pad handling
  if (curr_time >= _nextFlicker) {
    _nextFlicker = curr_time + _delay;

    int pad_x = 512 - analogRead(A5);
    int pad_y = 512 - analogRead(A4);

    if (_running) {
      char dX = 0;
      uint8_t rot = _rotation;

      if (pad_x < -JOYSTICK_THRESHOLD) {
        dX = -1;
      }
      if (pad_x > JOYSTICK_THRESHOLD) {
        dX = 1;
      }
      if (pad_y > JOYSTICK_THRESHOLD || !digitalRead(A3)) {
        rot = (rot + 1) % tetrominosMaxRotation[_tetrominoType];
      }

      if (!nextHorizontalCollision(dX, rot)) {
        _x += dX;
        _rotation = rot;
      }

      if (pad_y < -JOYSTICK_THRESHOLD) {
        incraseY();
      }
    } else {
      if (pad_y > JOYSTICK_THRESHOLD) {
        start();
      }
    }

    render();
  }
}

void Game::initGrid() {
  for (int i = 0; i < ((GRID_HEIGHT * GRID_WIDTH)); i++) {
    _grid->set(i, 0);
  }
}

void Game::initGame() {
  initGrid();
  _tetrominoType = getTetrominoType();
  _nextTetrominoType = getTetrominoType();
  _x = 3;
  _y = 0;
  _rotation = 0;
  _totalLines = 0;
  _score = 0;
  _level = 0;
}

inline uint8_t Game::getTetrominoType() {
  return (uint8_t)random(7);
}

void Game::start() {
  initGame();
  _running = true;
  _nextFlicker = millis();
  _nextFlickerY = millis();
}

void Game::stop() {
  _running = false;
}

void Game::clearAndRenderBackground() {
  _board->clear();
  _board->drawBackground();
  _board->drawScore(_score);
  _board->drawLevel(_level);
}

void Game::render() {
  //Serial.println(_tetrominoType);
  clearAndRenderBackground();
  _board->drawNextTetromino(_nextTetrominoType);
  _board->drawBlocs(_grid, _m, _n, _nHidden);
  _board->drawTetromino(
    _y,
    _x,
    _m,
    _n,
    _nHidden,
    _tetrominoType,
    _rotation);
  _board->commit();
}

bool Game::nextHorizontalCollision(char dX, uint8_t rotation) {

  for (uint8_t i = 0; i < 4; i++) {
    const uint8_t y = _y + (uint8_t)pgm_read_byte(&tetrominos[tetrominosIndexes[_tetrominoType] + rotation][1][i]);
    const char x = _x + (uint8_t)pgm_read_byte(&tetrominos[tetrominosIndexes[_tetrominoType] + rotation][0][i]) + dX;

    if (x < 0 || x > _n - 1 || _grid->get(y * _n + x) > 0) {
      return true;
    }
  }
  return false;
}

bool Game::nextVerticalCollision() {

  for (uint8_t i = 0; i < 4; i++) {
    const uint8_t y = _y + (uint8_t)pgm_read_byte(&tetrominos[tetrominosIndexes[_tetrominoType] + _rotation][1][i]) + 1;
    const char x = _x + (uint8_t)pgm_read_byte(&tetrominos[tetrominosIndexes[_tetrominoType] + _rotation][0][i]);

    if (y > _m - 1 || _grid->get(y * _n + x) > 0) {
      return true;
    }
  }
  return false;
}

void Game::fixTetrominoInGrid() {

  for (uint8_t i = 0; i < 4; i++) {
    const uint8_t y = _y + (uint8_t)pgm_read_byte(&tetrominos[tetrominosIndexes[_tetrominoType] + _rotation][1][i]);
    const uint8_t x = _x + (uint8_t)pgm_read_byte(&tetrominos[tetrominosIndexes[_tetrominoType] + _rotation][0][i]);
    _grid->set(y * _n + x, _tetrominoType + 1);
  }
}

void Game::newTetromino() {
  _y = 0;
  _x = 3;
  _rotation = 0;
  _tetrominoType = _nextTetrominoType;
  _nextTetrominoType = getTetrominoType();

  if (nextVerticalCollision()) {
    stop();
  }
}

void Game::incraseY() {
  if (nextVerticalCollision()) {
    fixTetrominoInGrid();
    checkLines();
    newTetromino();
  } else {
    _y++;
  }
}

void Game::incrementLevel() {
  _level = _totalLines / 10;
}

void Game::incrementScore(uint8_t nLines) {
  _score += getBaseScore(nLines) * (_level + 1);
}

long Game::getBaseScore(uint8_t nLines) {
  switch (nLines) {
    case 1:
      return 40;
    case 2:
      return 100;
    case 3:
      return 300;
    case 4:
      return 1200;
    default:
      return 0;
  }
}

void Game::deleteLine(uint8_t i) {
  for (uint8_t k = i; k > 0; k--) {
    for (uint8_t j = 0; j < _n; j++) {
      _grid->set(k * _n + j, _grid->get((k - 1) * _n + j));
    }
  }
}

void Game::checkLines() {
  uint8_t nlines = 0;

  for (uint8_t i = 0; i < _m; i++) {
    uint8_t nbric = 0;
    for (uint8_t j = 0; j < _n; j++) {
      nbric = nbric + (_grid->get(i * _n + j) > 0 ? 1 : 0);
    }
    if (nbric == _n) {
      nlines++;
      deleteLine(i);
    }
  }

  _totalLines += nlines;
  incrementLevel();
  incrementScore(nlines);
}