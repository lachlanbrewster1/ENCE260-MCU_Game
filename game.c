#include "system.h"
#include "pongBall.h"
#include "pongPaddle.h"
//#include "led.h"
#include "pio.h"
#include "ledController.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "pongGameStatus.h"
#include "ir_uart.h"

/** Welcome message to start game */
void welcomeMsg (void)
{
    /**rnadom*/
    tinygl_init (1000);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (5);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text ("WELCOME TO PONG! ");ls
}


int main (void)
{
    ir_uart_init ();
    pacer_init (500);
    navswitch_init ();
    system_init ();
    ledMatInit();

    bool player1 = 1;

    welcomeMsg();
    bool gameStart = 0;

    while (!gameStart) {
        navswitch_update();
        if (ir_uart_read_ready_p ()) {
            if (ir_uart_getc () == 'P') {
                player1 = 0;
                gameStart = 1;
            }
        }
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc('P');
            gameStart = 1;
        }
        tinygl_update ();
    }

    while (gameStart) {
        if (player1) {
            tinygl_text ("YOU ARE PLAYER 1");
        } else {
            tinygl_text ("YOU ARE PLAYER 2");
        }
        tinygl_update ();
    }




    paddle_struct_t paddle1 = initPaddle(1);
    paddle_struct_t paddle2 = initPaddle(2);
    ball_struct_t ball = initBall();


    int16_t counter = 0;
    bool up = 0;


    uint8_t newBitmap[5] = {0};
    uint8_t current_column = 0;


    while (1)
    {
        /**I know this is all a bit messy, will clean up!*/
        pacer_wait ();

        if (counter == 1000) {
            up = 1 - up;
            counter = 0;

        }
        bitMaker(newBitmap, paddle1.currCol1,paddle1.currRow1, 0);
        bitMaker(newBitmap, paddle1.currCol2,paddle1.currRow2, 0);
        bitMaker(newBitmap, paddle2.currCol1,paddle2.currRow1, 0);
        bitMaker(newBitmap, paddle2.currCol2,paddle2.currRow2, 0);

        if (counter % 50 == 0) {
            bitMaker(newBitmap, ball.currCol,ball.currRow, 0);
            ball = moveBall(ball);
        }

        paddle1 = movePaddle(paddle1, up);
        paddle2 = movePaddle(paddle2, !up);
        bitMaker(newBitmap, ball.currCol,ball.currRow, 1);
        bitMaker(newBitmap, paddle1.currCol1,paddle1.currRow1, 1);
        bitMaker(newBitmap, paddle1.currCol2,paddle1.currRow2, 1);
        bitMaker(newBitmap, paddle2.currCol1,paddle2.currRow1, 1);
        bitMaker(newBitmap, paddle2.currCol2,paddle2.currRow2, 1);

        counter++;

        display_column (newBitmap[current_column], current_column);

        current_column++;

        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }

    }
}
