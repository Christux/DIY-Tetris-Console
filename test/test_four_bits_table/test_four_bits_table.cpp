#include <Arduino.h>
#include <unity.h>
#include "FourBitsTable.h"

FourBitsTable* table;

void setUp() {
    table = new FourBitsTable(10);
}

void tearDown() {
    delete table;
}

void test_value_storage() {
    table->set(2, 14);
    TEST_ASSERT_EQUAL(14, table->get(2));
    TEST_ASSERT_EQUAL(0, table->get(9));
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_value_storage);
    UNITY_END();
}

void loop() {
    // Nothing to do for tests
}