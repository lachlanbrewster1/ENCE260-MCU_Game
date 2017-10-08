/** @file   pongBall.c
    @author G Lamont
    @date   6 October 2017
    @brief  pong ball module.
*/
#include "system.h"
#include "pacer.h"
#include "pio.h"


/** Structure to define a pong ball
 * contains balls current position
 * and current direction */
typedef struct ball_struct
{
    int8_t currRow;
    int8_t currCol;
    bool left;
    bool down;
} ball_struct_t;


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
void ledmat_pixel_set1 (int col, int row, bool state)
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

/** Initializes the ball
 * places the ball at pos (1,1) */
ball_struct_t initBall(void)
{
    ball_struct_t ball = {0,0,1,1};
    ledmat_pixel_set1 (ball.currCol, ball.currRow, 1);
    return ball;
}

/** Moves the given ball diagonally across the board
 * @param ball: given balls new position */
ball_struct_t moveBall (ball_struct_t ball)
{
    if (ball.left) {
        ball.currRow++;
    } else {
        ball.currRow--;
    }
    
    if (ball.down) {
        ball.currCol++;
    } else {
        ball.currCol--;
    }
    
        
    if (ball.currRow > 6 || ball.currRow < 0) {
        if (ball.left) {
            ball.currRow -= 2;
        } else {
            ball.currRow += 2;
        }
        ball.left = !(ball.left);
    }
    
    if (ball.currCol > 4 || ball.currCol < 0) {
        if (ball.down) {
            ball.currCol -= 2;
        } else {
            ball.currCol += 2;
        }
        ball.down = !(ball.down);
    }

    return ball;
}
