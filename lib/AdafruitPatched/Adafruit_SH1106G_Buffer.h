#include <Adafruit_SH110X.h>

#pragma once

class Adafruit_SH1106G_Buffer : public Adafruit_SH1106G  {

  public:
    Adafruit_SH1106G_Buffer(uint16_t w, uint16_t h, int8_t mosi_pin,
                                   int8_t sclk_pin, int8_t dc_pin,
                                   int8_t rst_pin, int8_t cs_pin,
                                   uint8_t *_buffer)
    : Adafruit_SH1106G(w, h, mosi_pin, sclk_pin, dc_pin, rst_pin, cs_pin) {
      Adafruit_GrayOLED::buffer = _buffer;
    }
};
