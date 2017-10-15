/** @file   pongDataSharing.h
    @author G Lamont and L Brewster
    @date   11 October 2017
    @brief  Pong game ir_uart data sharing module
*/

#include "system.h"
#include "pongPaddle.h"
#include "pongBall.h"
#include "ir_uart.h"
#include "ledController.h"

/** Checks received data from player 2's ir_uart
 *  updates paddle_2 position based on input
 *  @param paddle_2: the paddle to updated
 *  @return paddle_2: the updated paddle */
paddle_struct_t check_player_2(paddle_struct_t paddle_2);

/** Sends the ball and paddle_1 position data to player 2
 *  @param ball: the ball whose position is to be sent
 *  @param paddle_1: the paddle whose position is to be sent */
void send_data_to_p2(ball_struct_t ball, paddle_struct_t paddle_1);

/** Sends paddle_2 position data to player 1
 *  @param paddle_2: the paddle whose position is to be sent */
void send_data_to_p1(paddle_struct_t paddle_2);

/** Checks received data from player 1's ir_uart
 *  @param ball: the ball to be updated
 *  @param received: the char received from player 1
 *  @param bit_map: the bit map to be updated
 * @return ball: the updated ball */
ball_struct_t check_ball(ball_struct_t ball, char received, uint8_t *bit_map);

/** Checks received data from player 1's ir_uart
 *  @param paddle_1: the paddle to be updated
 *  @param received: the char received from player 1
 * @return paddle_1: the updated paddle */
paddle_struct_t check_player_1(paddle_struct_t paddle_1, char received);
