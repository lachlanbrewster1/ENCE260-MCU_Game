/** @file   pongBall.c
    @author G Lamont and L Brewster
    @date   6 October 2017
    @brief  Pong ball module. Initiates and moves a ball object
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledMat.h"
#include "pongPaddle.h"

#define MAX_COL 4
#define MIN_COL 0
#define MAX_ROW 6
#define MIN_ROW 0
#define BALL_SHIFT 2
#define ON 1
#define TRUE 1
#define FALSE 0
#define NUM_OF_LIVES 3
#define BALL_SPEED 200

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
    int16_t speed;
} ball_struct_t;

/** Initializes the ball
 * places the ball at pos (1,1) */
ball_struct_t init_ball(void)
{
    ball_struct_t ball = {MIN_ROW,MIN_COL,TRUE,TRUE, NUM_OF_LIVES, NUM_OF_LIVES, BALL_SPEED};
    ledmat_pixel_set (ball.curr_col, ball.curr_row, ON);
    return ball;
}

/** Checks if the ball has collided with the wall */
bool wall_collision(paddle_struct_t paddle, ball_struct_t ball)
{
    if(paddle.curr_row_1 == ball.curr_row) {
        if(ball.curr_col != paddle.curr_col_1 && ball.curr_col != paddle.curr_col_2) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }

    return FALSE;
}

/** Moves the given ball diagonally across the board
 * @param ball: given balls new position */
ball_struct_t move_ball (ball_struct_t ball, paddle_struct_t paddle_1, paddle_struct_t paddle_2)
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
    
        
    /** On collision with wall, the affected player loses one life 
     *  and the ball speed increases*/
    if(ball.curr_row == 0 && wall_collision(paddle_1, ball)) {
        ball.player_1_lives --;
        ball.speed -= 20;

    } else if (ball.curr_row == 6 && wall_collision(paddle_2, ball)) {
        ball.player_2_lives--;
        ball.speed -= 20;
    } else if ((ball.curr_row == 0 && !wall_collision(paddle_1, ball)) || (ball.curr_row == 6 && !wall_collision(paddle_2, ball))) {
        if (ball.left) {
            ball.curr_row -= BALL_SHIFT;
        } else {
            ball.curr_row += BALL_SHIFT;
        }
        ball.left = !(ball.left);
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
