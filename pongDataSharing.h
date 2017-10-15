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

paddle_struct_t check_player_2(paddle_struct_t paddle_2);

void send_data_to_p2(ball_struct_t ball, paddle_struct_t paddle_1);

void send_data_to_p1(paddle_struct_t paddle_2);

ball_struct_t check_ball(ball_struct_t ball, char received, uint8_t *bit_map);

paddle_struct_t check_player_1(paddle_struct_t paddle_1, char received);
