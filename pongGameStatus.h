/** @file   pongGameStatus.h
    @author G Lamont and L Brewster
    @date   11 October 2017
    @brief  Pong game status module; detects collisions and runs game logic
*/

#include "system.h"
#include "pongPaddle.h"
#include "pongBall.h"

/** Checks to see if a ball is colliding with the paddle or the ball
 *  @param paddle: the paddle being checked
 *  @param ball: the ball being checked
 *  @return true is ball hits paddle, 0 if ball hits wall*/
bool collision(paddle_struct_t paddle, ball_struct_t ball);
