/** @file   pongGameStatus.h
    @author G Lamont
    @date   11 October 2017
    @brief  pong paddle module.
*/

#include "system.h"

/** Checks to see if a ball is colliding with the paddle or the ball
 *  @param paddle: the paddle being checked
 *  @param ball: the ball being checked
 *  @return true is ball hits paddle, 0 if ball hits wall*/
bool collision(paddle_struct_t paddle, ball_struct_t ball);
