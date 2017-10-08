#include "system.h"
#include "pio.h"

/** Turns on the correct LEDs at the given row and column
 * @param row_pattern: pattern to switch on
 * @param current_column: the current column to turn on */
void display_column (uint8_t row_pattern, uint8_t current_column);

/** Takes a col and row and adds it to the given bit map
 * @param currBit: the bit map which the pattern to be applied to
 * @param col: the column the pattern is to be added to
 * @param row: the row to toggle
 * @param on: if on the row/col is set to 1, else 0 */
void bitMaker(uint8_t *currBit, uint8_t col, uint8_t row, bool on);

/** Initializes the LED mat on the UCFK
 * sets all pins to HIGH*/
void ledMatInit(void);

/** Clears the current bit map by setting it to all zeroes*/
void bitClear(uint8_t *currBit);
