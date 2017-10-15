/** @file   pongBall.h
    @author G Lamont and L Brewster
    @date   6 October 2017
    @brief  Pong ball module. Initiates and moves a ball object
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledMat.h"

#ifndef PONG_BALL_H
#define PONG_BALL_H

/** Structure to define a pong ball
 * contains balls current position
 * and current direction */
typedef struct ball_struct
{
    int8_t curr_row;
    int8_t curr_col;
    bool left;
    bool down;
    int8_t player_1_lives;
    int8_t player_2_lives;
} ball_struct_t;

/** Initializes the ball
 * places the ball at pos (1,1) */
ball_struct_t init_ball(void);

/** Moves the given ball diagonally across the board
 * @param ball: given balls new position */
ball_struct_t move_ball (ball_struct_t ball);

#endif
