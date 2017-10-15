/** @file   pongPaddle.h
    @author G Lamont and L Brewster
    @date   8 October 2017
    @brief  Pong paddle module, initiates and moves paddle object
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledMat.h"

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

/** Structure to define a pong paddle
 * contains paddels current position
 * and current player (1 or 2) */
typedef struct paddle_struct
{
    int8_t curr_row_1;
    int8_t curr_col_1;
    int8_t curr_row_2;
    int8_t curr_col_2;
    int8_t player;
} paddle_struct_t;

/** Initializes the paddle
 * places the paddle at pos */
paddle_struct_t init_paddle(int8_t playerNum);

/** Moves the given paddle up or down given button press
 * @param paddle: given paddles new position */
paddle_struct_t move_paddle (paddle_struct_t paddle, bool up);

#endif
