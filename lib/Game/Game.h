#include "FourBitsTable.h"
#include "Board.h"
#include "Tetrominos.h"

#pragma once

#define GRID_HEIGHT 22 /**< Total number of rows in the game grid */
#define GRID_WIDTH 10  /**< Number of columns in the game grid */
#define GRID_HIDDEN_ROWS 2 /**< Number of hidden rows at the top of the grid */
#define JOYSTICK_THRESHOLD 320 /**< Threshold value for joystick movement detection */

/**
 * @class Game
 * @brief Handles Tetris game logic and state.
 *
 * This class manages the grid, active tetromino, next tetromino,
 * score, level, and game timing. It also handles collisions, line clearing,
 * and rendering to the display via the Board class.
 */
class Game {
  protected:
    Board *_board; /**< Pointer to the Board instance for rendering */
    const uint8_t _nHidden; /**< Number of hidden rows */
    const uint8_t _m; /**< Number of rows */
    uint8_t _n; /**< Number of columns */
    FourBitsTable *_grid; /**< Pointer to the grid storing block states */
    uint8_t _level; /**< Current level */
    uint16_t _totalLines; /**< Total cleared lines */
    uint16_t _score; /**< Current score */
    uint8_t _tetrominoType; /**< Type of the active tetromino (0-6) */
    uint8_t _nextTetrominoType; /**< Type of the next tetromino (0-6) */
    uint8_t _rotation; /**< Current rotation of the active tetromino */
    uint8_t _x; /**< X position of the active tetromino in grid coordinates */
    uint8_t _y; /**< Y position of the active tetromino in grid coordinates */
    bool _running; /**< Game running flag */
    const uint16_t _delay; /**< Base delay for automatic piece falling */
    long _nextFlicker; /**< Next time for flicker update */
    uint16_t _delayY; /**< Delay between vertical moves */
    long _nextFlickerY; /**< Next time for vertical flicker */

    /** @brief Initializes the grid, clearing all cells */
    void initGrid();

    /** @brief Returns a random tetromino type (0-6) */
    uint8_t getTetrominoType();

    /** @brief Stops the game */
    void stop();

    /** @brief Clears the display and renders the static background */
    void clearAndRenderBackground();

    /** @brief Initializes game state variables */
    void initGame();

    /** @brief Renders the current game state */
    void render();

    /** @brief Moves the active tetromino down by one row */
    void incraseY();

    /**
     * @brief Checks for horizontal collision for the active tetromino
     * @param dX Horizontal movement (-1 = left, 1 = right)
     * @param rotation Rotation index to test
     * @return True if a collision would occur
     */
    bool nextHorizontalCollision(char dX, uint8_t rotation);

    /** @brief Checks for vertical collision of the active tetromino */
    bool nextVerticalCollision();

    /** @brief Fixes the active tetromino in the grid once it lands */
    void fixTetrominoInGrid();

    /** @brief Spawns a new tetromino at the top of the grid */
    void newTetromino();

    /** @brief Increments the level based on lines cleared */
    void incrementLevel();

    /**
     * @brief Increments the score based on lines cleared
     * @param nLines Number of lines cleared at once
     */
    void incrementScore(uint8_t nLines);

    /**
     * @brief Calculates the base score for a given number of lines
     * @param nLines Number of lines cleared
     * @return Score value
     */
    long getBaseScore(uint8_t nLines);

    /**
     * @brief Deletes a line from the grid
     * @param i Index of the line to delete
     */
    void deleteLine(uint8_t i);

    /** @brief Checks all lines and deletes any completed ones */
    void checkLines();

  public:
    /** @brief Destructor */
    ~Game() {};

    /**
     * @brief Constructs a Game instance
     * @param board Pointer to the Board instance for rendering
     * @param grid Pointer to a FourBitsTable instance representing the grid
     */
    Game(Board *board, FourBitsTable* grid);

    /** @brief Sets up the game (initializes grid, first piece, etc.) */
    void setup();

    /** @brief Handles game logic on each loop iteration */
    void handle();

    /** @brief Starts the game */
    void start();    
};