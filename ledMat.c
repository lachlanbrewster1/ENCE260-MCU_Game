/** @file   ledMat.c
    @author G Lamont and L Brewster
    @date   15 October 2017
    @brief  Led mat module, initiates and sets LED mat
*/

#include "system.h"
#include "pio.h"

#define MAX_COL 4
#define MIN_COL 0
#define MAX_ROW 6
#define MIN_ROW 0

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

/** Turn single LED within matrix on or off.
    @param col LED column number
    @param row LED row number
    @param state LED state  */
void ledmat_pixel_set (int col, int row, bool state)
{
    if (state)
    {
        pio_output_low (rows[row]);
        pio_output_low (cols[col]);
    }
    else
    {
        pio_output_high (rows[row]);
        pio_output_high (cols[col]);
    }
}


/** Initializes the LED mat on the UCFK
 * sets all pins to HIGH*/
void led_mat_init(void) {
    for(uint8_t row = MIN_ROW; row <= MAX_ROW; row++) {
        pio_config_set (rows[row], PIO_OUTPUT_HIGH);
    }
    
    for(uint8_t col = MIN_COL; col <= MAX_COL; col++) {
        pio_config_set (cols[col], PIO_OUTPUT_HIGH);
    }
}
