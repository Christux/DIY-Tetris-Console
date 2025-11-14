#include <Adafruit_SSD1306.h>
#include <Adafruit_SH110X.h>

#pragma once

/**
 * @class Board
 * @brief Handles drawing the Tetris game board on OLED displays.
 *
 * This class supports both SSD1306 and SH1106G displays.
 * It provides methods to draw the grid, tetrominos, next piece preview,
 * score, and level. Also handles low-level digit rendering.
 */
class Board
{
  protected:
    const uint8_t _xoffset; /**< X offset for drawing the board on screen */
    const uint8_t _yoffset; /**< Y offset for drawing the board on screen */

    static constexpr uint8_t BlockSize = 5; /**< Size of one block in pixels */
    static constexpr uint8_t BlockSpacing = 1; /**< Space between blocks in pixels */
    static constexpr uint8_t ScoreDigits = 8; /**< Number of digits used for score display */
    static constexpr uint8_t DigitSize = 4; /**< Size of digits in pixels */

    #if SCREEN == SSD1306
    Adafruit_SSD1306 *_display; /**< Pointer to SSD1306 display object */
    #else
    Adafruit_SH1106G *_display; /**< Pointer to SH1106G display object */
    #endif

    /**
     * @brief Calculates 10^n.
     * @param n Exponent.
     * @return 10 raised to the power n.
     */
    long power10(uint8_t n) const;

    /**
     * @brief Draws a number at a specified position.
     * @param n Number to draw.
     * @param d Number of digits to draw.
     * @param o Horizontal offset in pixels.
     */
    void drawNumber(long n, uint8_t d, uint8_t o);

    /**
     * @brief Draws a single digit at a specified position.
     * @param x X coordinate in pixels.
     * @param y Y coordinate in pixels.
     * @param digit Digit to draw (0-9).
     */
    void drawDigit(uint8_t x, uint8_t y, uint8_t digit);

  public:
    /**
     * @brief Destructor.
     */
    ~Board() {};

    #if SCREEN == SSD1306
    /**
     * @brief Constructs a Board object using an SSD1306 display.
     * @param display Pointer to an initialized Adafruit_SSD1306 display.
     */
    Board(Adafruit_SSD1306 *display);
    #else
    /**
     * @brief Constructs a Board object using an SH1106G display.
     * @param display Pointer to an initialized Adafruit_SH1106G display.
     */
    Board(Adafruit_SH1106G *display);
    #endif

    /**
     * @brief Initializes the board display.
     */
    void setup();

    /**
     * @brief Clears the board display.
     */
    void clear();

    /**
     * @brief Sends the buffer to the display (commits drawing operations).
     */
    void commit();

    /**
     * @brief Draws the static background for the game board.
     */
    void drawBackground() const;

    /**
     * @brief Draws the current score.
     * @param score Score value.
     */
    void drawScore(long score);

    /**
     * @brief Draws the current level.
     * @param level Level number.
     */
    void drawLevel(uint8_t level);

    /**
     * @brief Draws a single block (brick) on the board.
     * @param y Y coordinate in grid units.
     * @param x X coordinate in grid units.
     * @param m Number of rows in the grid.
     * @param n Number of columns in the grid.
     * @param nHidden Number of hidden rows at the top.
     * @param type Type of block (tetromino type).
     */
    void drawBric(char y, char x, uint8_t m, uint8_t n, uint8_t nHidden, uint8_t type);

    /**
     * @brief Draws the next tetromino preview.
     * @param type Tetromino type (0-6).
     */
    void drawNextTetromino(uint8_t type);

    /**
     * @brief Draws multiple blocks on the board from a grid.
     * @param grid Pointer to a FourBitsTable storing block types.
     * @param m Number of rows.
     * @param n Number of columns.
     * @param nHidden Number of hidden rows.
     */
    void drawBlocs(FourBitsTable* grid, uint8_t m, uint8_t n, uint8_t nHidden);

    /**
     * @brief Draws a tetromino on the board.
     * @param y Y coordinate in grid units.
     * @param x X coordinate in grid units.
     * @param m Number of rows in the grid.
     * @param n Number of columns in the grid.
     * @param nHidden Number of hidden rows.
     * @param type Tetromino type (0-6).
     * @param rotation Rotation index of the tetromino.
     */
    void drawTetromino(char y, char x, uint8_t m, uint8_t n, uint8_t nHidden, uint8_t type, uint8_t rotation);
};