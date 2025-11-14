#include <unity.h>
#include "Board.h"
#include <Adafruit_SH1106G_Buffer.h>

class BoardTester : public Board {
public:
	BoardTester(Adafruit_SH1106G_Buffer* b) : Board(b) {}
    using Board::power10; // exposes protected method
};

BoardTester *board;

void setUp() {
    board = new BoardTester((Adafruit_SH1106G_Buffer*)nullptr);
}

void tearDown() {
    delete board;
}

void test_power10() {
    TEST_ASSERT_EQUAL_INT16(1, board->power10(0));
	TEST_ASSERT_EQUAL_INT16(1000, board->power10(3));
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_power10);
    UNITY_END();
}

void loop() {}