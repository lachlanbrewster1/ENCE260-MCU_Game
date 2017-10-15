/** @file   ledMat.h
    @author G Lamont and L Brewster
    @date   15 October 2017
    @brief  Led mat module, initiates and sets LED mat
*/

#include "system.h"
#include "pio.h"

#ifndef LED_MAT_H
#define LED_MAT_H

/** Turn single LED within matrix on or off.
    @param col LED column number
    @param row LED row number
    @param state LED state  */
void ledmat_pixel_set (int col, int row, bool state);


/** Initializes the LED mat on the UCFK
 * sets all pins to HIGH*/
void led_mat_init(void);

#endif
