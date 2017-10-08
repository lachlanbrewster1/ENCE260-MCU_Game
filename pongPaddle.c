/** @file   pongPaddle.c
    @author G Lamont
    @date   8 October 2017
    @brief  pong paddle module.
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"

/** Structure to define a pong paddle
 * contains paddels current position
 * and current player (1 or 2) */
typedef struct paddle_struct
{
    int8_t currRow1;
    int8_t currCol1;
    int8_t currRow2;
    int8_t currCol2;
    int8_t player;
} paddle_struct_t;

/** Define PIO pins driving LED matrix rows and columns.  */
static pio_t ledmat_rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, LEDMAT_ROW4_PIO,
    LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO, LEDMAT_ROW7_PIO
};
static pio_t ledmat_cols[] =
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
        pio_output_low (ledmat_rows[row]);
        pio_output_low (ledmat_cols[col]);
    }
    else
    {
        pio_output_high (ledmat_rows[row]);
        pio_output_high (ledmat_cols[col]);
    }
}


/** Initializes the paddle
 * places the paddle */
paddle_struct_t initPaddle(int8_t playerNum)
{
    paddle_struct_t paddle = {6,0,6,1, playerNum};
    
    if (playerNum == 1) {
         paddle.currRow1 = 0;
         paddle.currRow2 = 0;
    }
   
    ledmat_pixel_set (paddle.currCol1, paddle.currRow1, 1);
    ledmat_pixel_set (paddle.currCol2, paddle.currRow2, 1);
    return paddle;
}

/** Moves the given paddle up or down given button press
 * @param paddle: given paddles new position */
paddle_struct_t movePaddle (paddle_struct_t paddle, bool up)
{
    
    if (up && paddle.currCol1 != 0) {
            paddle.currCol1--;
            paddle.currCol2--;
    }
    
    if (!up && paddle.currCol2 != 4) {
        paddle.currCol1++;
        paddle.currCol2++;
    }
    return paddle;
}
