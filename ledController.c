/** @file   ledController.c
    @author G Lamont and L Brewster
    @date   12 October 2017
    @brief  Led controller module, initiates and sets LED lights on UCFK
*/

#include "system.h"
#include "pio.h"
#include "pongPaddle.h"
#include "ledMat.h"

#define MAX_COL 4
#define MIN_COL 0
#define MAX_ROW 6
#define MIN_ROW 0

static uint8_t previous_column = MIN_COL;

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

/** Turns on the correct LEDs at the given row and column
 * @param row_pattern: pattern to switch on
 * @param current_column: the current column to turn on */
void display_column (uint8_t row_pattern, uint8_t current_column)
{

    pio_output_high (cols[previous_column]);

    
    for(uint8_t current_row = MIN_ROW; current_row <= MAX_ROW; current_row++) {
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
void bit_maker(uint8_t *curr_bit, uint8_t col, uint8_t row, bool on) {
    if(on) {
        curr_bit[col] = curr_bit[col] | (1 << row);
    } else {
        curr_bit[col] = curr_bit[col] & !(1 << row);
    }
    
}

/** Clears the current bit map by setting it to all zeroes*/
void bit_clear(uint8_t *curr_bit) {
    for(uint8_t col = MIN_COL; col <= MAX_COL; col++) {
        curr_bit[col] = MIN_COL;
    }
}

/** Updates the bitmap, turns bits on or on within each row
 *  @param bitmap: The bitmap to update
 *  @param paddle_1: the first paddle
 *  @param paddle_2: the second paddle
 *  @param on: turns bit on if true, else off*/
void update_bit_map(uint8_t *bit_map, paddle_struct_t paddle_1, paddle_struct_t paddle_2, bool on)
{
    bit_maker(bit_map, paddle_1.curr_col_1,paddle_1.curr_row_1, on);
    bit_maker(bit_map, paddle_1.curr_col_2,paddle_1.curr_row_2, on);
    bit_maker(bit_map, paddle_2.curr_col_1,paddle_2.curr_row_1, on);
    bit_maker(bit_map, paddle_2.curr_col_2,paddle_2.curr_row_2, on);
}

/** Updates the LED matrix display
 *  @param current_column: The current column to display
 *  @param bitmap: the mapping of bits to display*/
uint8_t update_display(uint8_t current_column, uint8_t *bit_map)
{
    display_column (bit_map[current_column], current_column);

    current_column++;

    if (current_column > (LEDMAT_COLS_NUM - 1))
    {
        current_column = MIN_COL;
    }
    return current_column;
}
