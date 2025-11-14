#include "FourBitsTable.h"
#include "Board.h"
#include "Tetrominos.h"

#pragma once

#define GRID_HEIGHT 22
#define GRID_WIDTH 10
#define GRID_HIDDEN_ROWS 2
#define JOYSTICK_THRESHOLD 320


class Game {
  protected:
    Board *_board;
    const uint8_t _nHidden;
    const uint8_t _m;
    uint8_t _n;
    FourBitsTable *_grid;
    uint8_t _level;
    uint16_t _totalLines;
    uint16_t _score;
    uint8_t _tetrominoType;
    uint8_t _nextTetrominoType;
    uint8_t _rotation;
    uint8_t _x;
    uint8_t _y;
    bool _running;
    const uint16_t _delay;
    long _nextFlicker;
    uint16_t _delayY;
    long _nextFlickerY;
    void initGrid();
    uint8_t getTetrominoType();
    void stop();
    void clearAndRenderBackground();
    void initGame();
    void render();
    void incraseY();
    bool nextHorizontalCollision(char dX, uint8_t rotation);
    bool nextVerticalCollision();
    void fixTetrominoInGrid();
    void newTetromino();
    void incrementLevel();
    void incrementScore(uint8_t nLines);
    long getBaseScore(uint8_t nLines);
    void deleteLine(uint8_t i);
    void checkLines();

  public:
    ~Game() {};
    Game(Board *board, FourBitsTable* grid);
    void setup();
    void handle();
    void start();    
};
