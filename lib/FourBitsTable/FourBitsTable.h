#include <Arduino.h>

#pragma once

/**
 * @class FourBitsTable
 * @brief Represents a compact table storing 4-bit values.
 *
 * This class allows storing multiple 4-bit values efficiently
 * in a byte array, useful for memory-constrained environments
 * like Arduino.
 */
class FourBitsTable {
  public:
    /**
     * @brief Constructs a FourBitsTable with a given size.
     * @param size Number of 4-bit values to store.
     */
    FourBitsTable(uint8_t size);

    /**
     * @brief Constructs a FourBitsTable using existing data.
     * @param size Number of 4-bit values.
     * @param data Pointer to an existing byte array to use as storage.
     */
    FourBitsTable(uint8_t size, uint8_t* data);

    /**
     * @brief Destructor.
     */
    ~FourBitsTable() {};

    /**
     * @brief Sets a 4-bit value at the specified index.
     * @param index Index in the table (0-based).
     * @param value Value to set (0–15).
     */
    void set(uint8_t index, uint8_t value);

    /**
     * @brief Gets the 4-bit value at the specified index.
     * @param index Index in the table (0-based).
     * @return The 4-bit value stored at the given index.
     */
    uint8_t get(uint8_t index) const;

    /**
     * @brief Returns the number of 4-bit values stored.
     * @return Table length.
     */
    uint8_t length() const;

  private:
    uint8_t _size;   ///< Number of 4-bit values in the table
    uint8_t* _data;  ///< Pointer to the byte array storing values
};
