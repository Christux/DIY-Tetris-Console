/*
  DIY Tetris Console
  -------------------
  This project is an educational, non-commercial recreation of classic 
  falling-block puzzle game mechanics. The purpose is purely pedagogical:
  exploring how to fit a complete game into an Arduino Nano, a microcontroller
  with extremely limited memory and processing power.

  Technical focus:
  - Memory-efficient game logic (2 KB RAM on ATmega328P)
  - Minimalist graphics for OLED/LCD displays
  - Real-time input handling
  - Tight game loop optimization for low-end hardware

  Legal Notice:
  - This project is NOT affiliated with, endorsed by, or licensed from the Tetris brand.
  - The name "DIY Tetris Console" refers only to the gameplay style being reimplemented 
    for educational experimentation.
  - All code, graphics, and sounds are original or free-to-use assets.
  - No copyrighted material from the official Tetris game has been used.
  - This project is strictly NON-COMMERCIAL.

  License: MIT License (see LICENSE)
  Author: Christophe Rubeck
  GitHub: https://github.com/Christux/DIY-Tetris-Console
*/

#include <Arduino.h>
#include <SPI.h>
#include "Config.h"
#include "Adafruit_SSD1306_Buffer.h"
#include "Adafruit_SH1106G_Buffer.h"
#include "FourBitsTable.h"
#include "Board.h"
#include "Tetrominos.h"
#include "Melody.h"
#include "Game.h"
#include "Logo.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SH110X_NO_SPLASH 0
#define SSD1306_NO_SPLASH 0

#define OLED_MOSI 9 // SDA
#define OLED_CLK 10 // SCK
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13

#define JOYPAD_INPUT A3

// Allocates memory for this tables first in order to avoid fragmentation !
uint8_t buffer[(SCREEN_WIDTH * SCREEN_HEIGHT + 7) / 8];
uint8_t gridData[(GRID_HEIGHT * GRID_WIDTH + 1) / 2];

#if SCREEN == SSD1306

Adafruit_SSD1306_Buffer display(SCREEN_WIDTH, SCREEN_HEIGHT,
                                OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS,
                                buffer);
#else

Adafruit_SH1106G_Buffer display(SCREEN_WIDTH, SCREEN_HEIGHT,
                                OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS,
                                buffer);
#endif

FourBitsTable grid((GRID_HEIGHT * GRID_WIDTH), gridData);

Board board(&display);

Game tetris(&board, &grid);

// uint8_t buttonState = 0;

void setup()
{
  // Serial.begin(9600);

  // pinMode(8, OUTPUT);
  // pinMode(3, OUTPUT);
  pinMode(JOYPAD_INPUT, INPUT_PULLUP);

#if SCREEN == SSD1306
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    // Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.setRotation(1);
#else
  display.begin(0, true);
  display.setRotation(3);
#endif

  display.clearDisplay();
  display.drawBitmap(0, 0, logoBitmap, 64, 128, WHITE);
  display.display();
  delay(3000);

  randomSeed(analogRead(A0));
  random(7); // bug, first rand is allways 0

  tetris.setup();
  tetris.start();
}

void loop()
{
  tetris.handle();
}
