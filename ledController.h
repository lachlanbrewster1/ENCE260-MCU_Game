/** @file   ledController.h
    @author G Lamont and L Brewster
    @date   12 October 2017
    @brief  Led controller module, initiates and sets LED lights on UCFK
*/

#include "system.h"
#include "pio.h"
#include "pongPaddle.h"
#include "ledMat.h"

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H


/** Turns on the correct LEDs at the given row and column
 * @param row_pattern: pattern to switch on
 * @param current_column: the current column to turn on */
void display_column (uint8_t row_pattern, uint8_t current_column);

/** Takes a col and row and adds it to the given bit map
 * @param currBit: the bit map which the pattern to be applied to
 * @param col: the column the pattern is to be added to
 * @param row: the row to toggle
 * @param on: if on the row/col is set to 1, else 0 */
void bit_maker(uint8_t *curr_bit, uint8_t col, uint8_t row, bool on);

/** Clears the current bit map by setting it to all zeroes*/
void bit_clear(uint8_t *curr_bit);

/** Updates the bitmap, turns bits on or on within each row
 *  @param bitmap: The bitmap to update
 *  @param paddle_1: the first paddle
 *  @param paddle_2: the second paddle
 *  @param on: turns bit on if true, else off*/
void update_bit_map(uint8_t *bit_map, paddle_struct_t paddle_1, paddle_struct_t paddle_2, bool on);

/** Updates the LED matrix display
 *  @param current_column: The current column to display
 *  @param bitmap: the mapping of bits to display*/
uint8_t update_display(uint8_t current_column, uint8_t *bit_map);

#endif
