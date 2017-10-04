#include "system.h"
//#include "pongBall.h"
//#include "pongPaddle.h"
//#include "led.h"
//#include "pio.h"
//#include "ledmat.h"
//#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
//#include "pongGameStatus.h"

void welcomeMsg (void)
{
    tinygl_init (1000);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (20);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text ("WELCOME TO PONG! ");
}

int main (void)
{
    system_init ();
    pacer_init (1000);
    welcomeMsg();


    while (1)
    {
        pacer_wait ();
        tinygl_update ();

    }
}
