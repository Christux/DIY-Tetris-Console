#include <Arduino.h>

#pragma once

class FourBitsTable {
  public:
    FourBitsTable(uint8_t size);
    FourBitsTable(uint8_t size, uint8_t* data);
    ~FourBitsTable() {};

    void set(uint8_t index, uint8_t value);
    uint8_t get(uint8_t index) const;
    uint8_t length() const;

  private:
    uint8_t _size;
    uint8_t* _data;
};
