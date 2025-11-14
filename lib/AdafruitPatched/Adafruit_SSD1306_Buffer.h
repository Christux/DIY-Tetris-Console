#include <Adafruit_SSD1306.h>

#pragma once

class Adafruit_SSD1306_Buffer : public Adafruit_SSD1306 {

  public:
    Adafruit_SSD1306_Buffer(uint16_t w, uint16_t h, int8_t mosi_pin,
                                   int8_t sclk_pin, int8_t dc_pin,
                                   int8_t rst_pin, int8_t cs_pin,
                                   uint8_t *_buffer)
    : Adafruit_SSD1306(w, h, mosi_pin, sclk_pin, dc_pin, rst_pin, cs_pin) {
      Adafruit_SSD1306::buffer = _buffer;
     }
};