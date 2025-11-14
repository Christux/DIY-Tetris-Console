#include <Adafruit_SSD1306.h>
#include <Adafruit_SH110X.h>

#pragma once

class Board
  {
    protected:
			const uint8_t _xoffset;
      const uint8_t _yoffset;
      static constexpr uint8_t BlockSize = 5;
      static constexpr uint8_t BlockSpacing = 1;
      static constexpr uint8_t ScoreDigits = 8;
      static constexpr uint8_t DigitSize = 4;
      #if SCREEN == SSD1306
      Adafruit_SSD1306 *_display;
      #else
      Adafruit_SH1106G *_display;
      #endif
      long power10(uint8_t n) const;
      void drawNumber(long n, uint8_t d, uint8_t o);
      void drawDigit(uint8_t x, uint8_t y, uint8_t digit);
      
    public:
      ~Board() {};
      #if SCREEN == SSD1306
      Board(Adafruit_SSD1306 *display);
      #else
      Board(Adafruit_SH1106G *display);
      #endif
      void setup();
      void clear();
      void commit();
      void drawBackground() const;
      void drawScore(long score);
      void drawLevel(uint8_t level);
      void drawBric(char y, char x, uint8_t m, uint8_t n, uint8_t nHidden, uint8_t type);
      void drawNextTetromino(uint8_t type);
      void drawBlocs(FourBitsTable* grid, uint8_t m, uint8_t n, uint8_t nHidden);
      void drawTetromino(char y, char x, uint8_t m, uint8_t n, uint8_t nHidden, uint8_t type, uint8_t rotation);
  };