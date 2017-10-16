/** @file   game.c
    @author G Lamont and L Brewster
    @date   15 October 2017
    @brief  Pong game: Two players compete to return the bouncing ball;
*/

#include "system.h"
#include "pongBall.h"
#include "pongPaddle.h"
#include "pio.h"
#include "ledController.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"
#include "pongDataSharing.h"

#define UP 1
#define DOWN 0
#define PLAYER_1 1
#define PLAYER_2 2
#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
#define LOOP_RATE 500
#define TEXT_SPEED 5

bool is_player1 = TRUE;

/** Welcome message to start game
 *  prints until one player presses the button*/
void scrolling_msg (const char* message)
{
    tinygl_init (LOOP_RATE * 2);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (TEXT_SPEED);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text (message);
}

/** The game starting message, will display a nice message
 *  and also based on button press, decides who player 1 is */
void game_message(const char* message)
{
    scrolling_msg(message);
    bool game_start = FALSE;

    while (!game_start) {
        navswitch_update();
        if (ir_uart_read_ready_p ()) {
            if (ir_uart_getc () == 'p') {
                is_player1 = FALSE;
                game_start = TRUE;
            }
        }
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc('p');
            game_start = TRUE;
        }
        tinygl_update ();
    }
}

/** Polls button and moves the paddle accordingly*/
paddle_struct_t poll_paddle_button(paddle_struct_t paddle)
{
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        paddle = move_paddle(paddle, DOWN);
    }
    else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        paddle = move_paddle(paddle, UP);
    }
    return paddle;
}

int main (void)
{
    is_player1 = TRUE;
    
    pacer_init (LOOP_RATE);
    navswitch_init ();
    system_init ();
    ir_uart_init ();
    
    const char* welcome = "WELCOME TO PONG! ";
    game_message(welcome);
    
    led_mat_init();

    paddle_struct_t paddle_1 = init_paddle(PLAYER_1);
    paddle_struct_t paddle_2 = init_paddle(PLAYER_2);
    ball_struct_t ball = init_ball();

    char received;
    char send;

    int16_t counter = 0;

    uint8_t bit_map[5] = {0};
    uint8_t current_column = 0;

    bool won = FALSE;


    while (TRUE)
    {
        pacer_wait();
        update_bit_map(bit_map, paddle_1, paddle_2, OFF) ;

        if (is_player1) {

            paddle_1 = poll_paddle_button(paddle_1);

            if (ir_uart_read_ready_p()) {
                paddle_2 = check_player_2(paddle_2);
            }

            if (counter == ball.speed) {
                bit_maker(bit_map, ball.curr_col,ball.curr_row, OFF);
                ball = move_ball(ball, paddle_1, paddle_2);

                send_data_to_p2(ball, paddle_1);
                counter = 0;
                
                if(ball.player_1_lives == 0) {
                    won = FALSE;
                    send = 'w';
                    ir_uart_putc(send);
                    break;
                } else if(ball.player_2_lives == 0) {
                    send = 'l';
                    ir_uart_putc(send);
                    won = TRUE;
                    break;
                }
            }

        } else {
            paddle_2 = poll_paddle_button(paddle_2);
            if (counter % ball.speed / 2 == 0) {
                send_data_to_p1(paddle_2);
            }
            if (ir_uart_read_ready_p()) {
                received = ir_uart_getc();
                ball = check_ball(ball, received, bit_map);
                paddle_1 = check_player_1(paddle_1, received);
                if (received == 'w' || received == 'l'){
                    if(received == 'w') {
                        won = TRUE;
                    } else {
                        won = FALSE;
                    }
                    break;
                }
            }
        }

        bit_maker(bit_map, ball.curr_col,ball.curr_row, ON);
        update_bit_map(bit_map, paddle_1, paddle_2, ON);
        counter++;
        current_column = update_display(current_column, bit_map);
    }
    
    const char* message;
    
    if(won) {
        message = "YOU WON!";
    } else {
        message = "YOU LOST!";
    }
    
    game_message(message);
    main();
}
