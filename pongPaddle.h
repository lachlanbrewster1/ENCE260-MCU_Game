/** @file   pongPaddle.h
    @author G Lamont
    @date   8 October 2017
    @brief  pong paddle module.
*/

#include "system.h"
#include "pacer.h"
#include "pio.h"

/** Turn single LED within matrix on or off.
    @param col LED column number
    @param row LED row number
    @param state LED state  */
void ledmat_pixel_set (int col, int row, bool state);


/** Initialise LED matrix PIO pins.  */
void ledmatPaddle_init (void);

/** Structure to define a pong paddle
 * contains paddels current position
 * and current player (1 or 2) */
typedef struct paddle_struct
{
    int8_t currRow1;
    int8_t currCol1;
    int8_t currRow2;
    int8_t currCol2;
    int8_t player;
} paddle_struct_t;

/** Initializes the paddle
 * places the paddle at pos */
paddle_struct_t initPaddle(int8_t playerNum);

/** Moves the given paddle up or down given button press
 * @param paddle given paddle to move */
paddle_struct_t movePaddle (paddle_struct_t paddle, bool up);
