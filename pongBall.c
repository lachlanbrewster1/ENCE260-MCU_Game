/** @file   pongBall.c
    @author G Lamont and L Brewster
    @date   6 October 2017
    @brief  Pong ball module. Initiates and moves a ball object
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledMat.h"

#define MAX_COL 4
#define MIN_COL 0
#define MAX_ROW 6
#define MIN_ROW 0
#define BALL_SHIFT 2
#define ON 1
#define TRUE 1
#define NUM_OF_LIVES 3

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
ball_struct_t init_ball(void)
{
    ball_struct_t ball = {MIN_ROW,MIN_COL,TRUE,TRUE, NUM_OF_LIVES, NUM_OF_LIVES};
    ledmat_pixel_set (ball.curr_col, ball.curr_row, ON);
    return ball;
}

/** Moves the given ball diagonally across the board
 * @param ball: given balls new position */
ball_struct_t move_ball (ball_struct_t ball)
{
    if (ball.left) {
        ball.curr_row++;
    } else {
        ball.curr_row--;
    }

    if (ball.down) {
        ball.curr_col++;
    } else {
        ball.curr_col--;
    }


    if (ball.curr_row > MAX_ROW || ball.curr_row < MIN_ROW) {
        if (ball.left) {
            ball.curr_row -= BALL_SHIFT;
        } else {
            ball.curr_row += BALL_SHIFT;
        }
        ball.left = !(ball.left);
    }

    if (ball.curr_col > MAX_COL || ball.curr_col < MIN_COL) {
        if (ball.down) {
            ball.curr_col -= BALL_SHIFT;
        } else {
            ball.curr_col += BALL_SHIFT;
        }
        ball.down = !(ball.down);
    }

    return ball;
}
