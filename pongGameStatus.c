/** @file   pongGameStatus.c
    @author G Lamont
    @date   11 October 2017
    @brief  pong paddle module.
*/

#include "system.h"
#include "pongPaddle.h"
#include "pongBall.h"

/** Checks to see if a ball is colliding with the paddle or the ball
 *  @param paddle: the paddle being checked
 *  @param ball: the ball being checked
 *  @return true is ball hits paddle, 0 if ball hits wall*/
bool collision(paddle_struct_t paddle, ball_struct_t ball)
{
    if (paddle.currRow1 == ball.currRow && paddle.currCol1 == ball.currCol) {
        return 1;
    }

    if (paddle.currRow2 == ball.currRow && paddle.currCol2 == ball.currCol) {
        return 1;
    }

    return 0;
}
