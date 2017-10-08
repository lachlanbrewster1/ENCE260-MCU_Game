#include "system.h"
#include "pio.h"

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

static uint8_t previous_column = 0;

/** Turns on the correct LEDs at the given row and column
 * @param row_pattern: pattern to switch on
 * @param current_column: the current column to turn on */
void display_column (uint8_t row_pattern, uint8_t current_column)
{

    pio_output_high (cols[previous_column]);

    
    for(uint8_t current_row = 0; current_row < 7; current_row++) {
        if ((row_pattern >> current_row & 1)) {
            pio_output_low (rows[current_row]);
        } else {
             pio_output_high (rows[current_row]);
        }
    }
    
    pio_output_low (cols[current_column]);
    previous_column = current_column;

}

/** Takes a col and row and adds it to the given bit map
 * @param currBit: the bit map which the pattern to be applied to
 * @param col: the column the pattern is to be added to
 * @param row: the row to toggle
 * @param on: if on the row/col is set to 1, else 0 */
void bitMaker(uint8_t *currBit, uint8_t col, uint8_t row, bool on) {
    if(on) {
        currBit[col] = currBit[col] | (1 << row);
    } else {
        currBit[col] = currBit[col] & !(1 << row);
    }
    
}

/** Initializes the LED mat on the UCFK
 * sets all pins to HIGH*/
void ledMatInit(void) {
    for(uint8_t row = 0; row < 7; row++) {
        pio_config_set (rows[row], PIO_OUTPUT_HIGH);
    }
    
    for(uint8_t col = 0; col < 5; col++) {
        pio_config_set (cols[col], PIO_OUTPUT_HIGH);
    }
}

/** Clears the current bit map by setting it to all zeroes*/
void bitClear(uint8_t *currBit) {
    for(uint8_t col = 0; col < 5; col++) {
        currBit[col] = 0;
    }
}
