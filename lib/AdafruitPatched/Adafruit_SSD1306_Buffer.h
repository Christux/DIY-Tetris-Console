#include <Adafruit_SSD1306.h>

#pragma once

/**
 * @class Adafruit_SSD1306_Buffer
 * @brief Specialized SSD1306 display class using a user-provided buffer.
 *
 * This class extends Adafruit_SSD1306 to allow using an external
 * memory buffer for the display. Useful for managing memory manually
 * or sharing a buffer between multiple displays.
 */
class Adafruit_SSD1306_Buffer : public Adafruit_SSD1306 {

  public:
    /**
     * @brief Constructs an Adafruit_SSD1306 display with a custom buffer.
     * @param w Display width in pixels.
     * @param h Display height in pixels.
     * @param mosi_pin MOSI pin number.
     * @param sclk_pin Clock pin number.
     * @param dc_pin Data/Command pin number.
     * @param rst_pin Reset pin number.
     * @param cs_pin Chip select pin number.
     * @param _buffer Pointer to an external buffer to use for the display.
     *
     * @note The provided buffer must be large enough to hold the full
     *       display data (width * height / 8 bytes for monochrome displays).
     */
    Adafruit_SSD1306_Buffer(uint16_t w, uint16_t h, int8_t mosi_pin,
                                   int8_t sclk_pin, int8_t dc_pin,
                                   int8_t rst_pin, int8_t cs_pin,
                                   uint8_t *_buffer)
    : Adafruit_SSD1306(w, h, mosi_pin, sclk_pin, dc_pin, rst_pin, cs_pin) {
      Adafruit_SSD1306::buffer = _buffer;
     }
};