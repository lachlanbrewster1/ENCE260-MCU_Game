/** @file   pongBall.h
    @author G Lamont
    @date   6 October 2017
    @brief  pong ball module.
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"


/** Turn single LED within matrix on or off.
    @param col LED column number
    @param row LED row number
    @param state LED state  */
void ledmat_pixel_set (int col, int row, bool state);


/** Initialise LED matrix PIO pins.  */
void ledmatBall_init (void);

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

/** Initializes the ball
 * places the ball at pos (1,1) */
ball_struct_t initBall(void);

/** Moves the given ball diagonally across the board
 * @param ball given ball to move */
ball_struct_t move_ball (ball_struct_t ball);