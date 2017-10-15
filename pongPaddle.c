/** @file   pongPaddle.c
    @author G Lamont and L Brewster
    @date   8 October 2017
    @brief  Pong paddle module, initiates and moves paddle object
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledMat.h"

#define MAX_COL 4
#define MIN_COL 0
#define MAX_ROW 6
#define MIN_ROW 0
#define ON 1

/** Structure to define a pong paddle
 * contains paddels current position
 * and current player (1 or 2) */
typedef struct paddle_struct
{
    int8_t curr_row_1;
    int8_t curr_col_1;
    int8_t curr_row_2;
    int8_t curr_col_2;
    int8_t player;
} paddle_struct_t;

/** Initializes the paddle
 * places the paddle */
paddle_struct_t init_paddle(int8_t playerNum)
{
    paddle_struct_t paddle = {MAX_ROW,MIN_COL,MAX_ROW,MIN_COL + 1, playerNum};
    
    if (playerNum == 1) {
         paddle.curr_row_1 = MIN_ROW;
         paddle.curr_row_2 = MIN_ROW;
    }
   
    ledmat_pixel_set (paddle.curr_col_1, paddle.curr_row_1, ON);
    ledmat_pixel_set (paddle.curr_col_2, paddle.curr_row_2, ON);
    return paddle;
}

/** Moves the given paddle up or down given button press
 * @param paddle: given paddles new position */
paddle_struct_t move_paddle (paddle_struct_t paddle, bool up)
{
    
    if (up && paddle.curr_col_1 != MIN_COL) {
            paddle.curr_col_1--;
            paddle.curr_col_2--;
    }
    
    if (!up && paddle.curr_col_2 != MAX_COL) {
        paddle.curr_col_1++;
        paddle.curr_col_2++;
    }
    return paddle;
}
