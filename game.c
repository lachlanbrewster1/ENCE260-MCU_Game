#include "system.h"
#include "pongBall.h"
#include "pongPaddle.h"
#include "pio.h"
#include "ledController.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "pongGameStatus.h"
#include "ir_uart.h"

#define UP 1
#define DOWN 0

bool isPlayer1 = 1;

/** Welcome message to start game */
void welcomeMsg (void)
{
    tinygl_init (1000);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (5);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text ("WELCOME TO PONG! ");
}

/** Updates the LED matrix display
 *  @param current_column: The current column to display
 *  @param bitmap: the mapping of bits to display*/
uint8_t updateDisplay(uint8_t current_column, uint8_t *bitMap)
{
    display_column (bitMap[current_column], current_column);

    current_column++;

    if (current_column > (LEDMAT_COLS_NUM - 1))
    {
        current_column = 0;
    }
    return current_column;
}

/** Updates the bitmap, turns bits on or on within each row
 *  @param bitmap: The bitmap to update
 *  @param paddle1: the first paddle
 *  @param paddle2: the second paddle
 *  @param on: turns bit on if true, else off*/
void updateBitMap(uint8_t *bitMap, paddle_struct_t paddle1, paddle_struct_t paddle2, bool on)
{
    bitMaker(bitMap, paddle1.currCol1,paddle1.currRow1, on);
    bitMaker(bitMap, paddle1.currCol2,paddle1.currRow2, on);
    bitMaker(bitMap, paddle2.currCol1,paddle2.currRow1, on);
    bitMaker(bitMap, paddle2.currCol2,paddle2.currRow2, on);
}

/** The game starting message, will display a nice message
 *  and also based on button press, decides who player 1 is */
void gameStart(void)
{
    welcomeMsg();
    bool gameStart = 0;

    while (!gameStart) {
        navswitch_update();
        if (ir_uart_read_ready_p ()) {
            if (ir_uart_getc () == 'p') {
                isPlayer1 = 0;
                gameStart = 1;
            }
        }
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc('p');
            gameStart = 1;
        }
        tinygl_update ();
    }
}

/** Polls button and moves the paddle accordingly*/
paddle_struct_t pollPaddleButton(paddle_struct_t paddle)
{
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        paddle = movePaddle(paddle, DOWN);
    }
    else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        paddle = movePaddle(paddle, UP);
    }
    return paddle;
}

int main (void)
{
    pacer_init (500);
    navswitch_init ();
    system_init ();
    ledMatInit();
    ir_uart_init ();

    gameStart();

    paddle_struct_t paddle1 = initPaddle(1);
    paddle_struct_t paddle2 = initPaddle(2);
    ball_struct_t ball = initBall();

    char received;
    char send;

    int16_t counter = 0;

    uint8_t newBitmap[5] = {0};
    uint8_t current_column = 0;

    while (1)
    {
        pacer_wait ();
        updateBitMap(newBitmap, paddle1, paddle2, 0) ;

        if (isPlayer1) {

            if (counter == 200) {
                bitMaker(newBitmap, ball.currCol,ball.currRow, 0);
                ball = moveBall(ball);
                send = (char) (ball.currRow * 10 + ball.currCol + 32);
                ir_uart_putc(send);
                send = 100 + paddle1.currCol1;
                ir_uart_putc(send);
                counter = 0;
            }

            paddle1 = pollPaddleButton(paddle1);

            if (ir_uart_read_ready_p()) {
                received = ir_uart_getc();
                if (received >= 120 && received <= 123) {
                    paddle2.currCol1 = received - 120;
                    paddle2.currCol2 = received - 119;

                }
            }

            /*Collisions
            if (!collision(paddle1, ball) && ball.currRow == 0) {
                Player 1 has lost
                send = 'w';
                ir_uart_putc(send);
                break;
            } else if (!collision(paddle2, ball) && ball.currRow == 6) {
                /Player 2 has lost
                send = 'l';
                ir_uart_putc(send);
                break;
            }*/

        } else {
            paddle2 = pollPaddleButton(paddle2);
            if (counter % 100 == 0) {
                send = 120 + paddle2.currCol1;
                ir_uart_putc(send);
            }


            if (ir_uart_read_ready_p()) {
                received = ir_uart_getc();

                if (received <= 96 && received >= 32) {
                    received -= 32;
                    bitMaker(newBitmap, ball.currCol,ball.currRow, 0);
                    ball.currCol = received % 10;
                    ball.currRow = (received - ball.currCol ) / 10;

                } else if (received >= 100 && received <= 103) {
                    paddle1.currCol1 = received - 100;
                    paddle1.currCol2 = received - 99;
                } else {
                    //break;
                }
            }
        }

        bitMaker(newBitmap, ball.currCol,ball.currRow, 1);
        updateBitMap(newBitmap, paddle1, paddle2, 1);
        counter++;
        current_column = updateDisplay(current_column, newBitmap);
    }
}

