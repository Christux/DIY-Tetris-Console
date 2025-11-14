#include "FourBitsTable.h"

FourBitsTable::FourBitsTable(uint8_t size) : _size(size) {
  uint8_t numBytes = (size + 1) / 2;
  _data = new uint8_t[numBytes];
  memset(_data, 0, numBytes);
}

FourBitsTable::FourBitsTable(uint8_t size, uint8_t* data) :
 _size(size),
 _data(data)
{}

void FourBitsTable::set(uint8_t index, uint8_t value) {
  if (index >= _size || value > 15) return;

  uint8_t byteIndex = index / 2;
  bool highNibble = (index % 2 == 0);

  if (highNibble) {
    _data[byteIndex] &= 0x0F;
    _data[byteIndex] |= (value << 4);
  } else {
    _data[byteIndex] &= 0xF0;
    _data[byteIndex] |= (value & 0x0F);
  }
}

uint8_t FourBitsTable::get(uint8_t index) const {
  if (index >= _size) return 0;

  uint8_t byteIndex = index / 2;
  bool highNibble = (index % 2 == 0);

  if (highNibble) {
    return (_data[byteIndex] >> 4) & 0x0F;
  } else {
    return _data[byteIndex] & 0x0F;
  }
}

uint8_t FourBitsTable::length() const {
  return _size;
}