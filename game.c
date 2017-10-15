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
#define BALL_SPEED 200
#define NUM_OF_LIVES 3

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
void game_start(void)
{
    const char* welcome = "WELCOME TO PONG! ";
    scrolling_msg(welcome);
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

int main (void)
{
    pacer_init (LOOP_RATE);
    navswitch_init ();
    system_init ();
    led_mat_init();
    ir_uart_init ();

    game_start();

    paddle_struct_t paddle_1 = init_paddle(PLAYER_1);
    paddle_struct_t paddle_2 = init_paddle(PLAYER_2);
    ball_struct_t ball = init_ball();

    char received;
    char send;

    int16_t counter = 0;

    uint8_t bit_map[5] = {0};
    uint8_t current_column = 0;

    int8_t player_1_lives = NUM_OF_LIVES;
    int8_t player_2_lives = NUM_OF_LIVES;

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

            if (counter == BALL_SPEED) {
                bit_maker(bit_map, ball.curr_col,ball.curr_row, OFF);
                ball = move_ball(ball);

                send_data_to_p2(ball, paddle_1);
                counter = 0;

                if(ball.curr_row == 0 && wall_collision(paddle_1, ball)) {
                    player_1_lives--;
                    if(player_1_lives == 0) {
                        won = FALSE;
                        send = 'w';
                        ir_uart_putc(send);
                        break;
                    }
                } else if (ball.curr_row == 6 && wall_collision(paddle_2, ball)) {
                    player_2_lives--;
                    if(player_2_lives == 0) {
                        send = 'l';
                        ir_uart_putc(send);
                        won = TRUE;
                        break;
                    }
                }
            }

        } else {
            paddle_2 = poll_paddle_button(paddle_2);
            if (counter % BALL_SPEED / 2 == 0) {
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

    if(won) {
        scrolling_msg("YOU WON!");
    } else {
        scrolling_msg("YOU LOST!");
    }

    pacer_init (LOOP_RATE * 10);

    bool restart = FALSE;

    while(!restart) {
        pacer_wait();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            restart = TRUE;
        }
        tinygl_update();

    }
    main();
}

