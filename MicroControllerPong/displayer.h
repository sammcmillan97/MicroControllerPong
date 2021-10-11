#ifndef DISPLAYER_H
#define DISPLAYER_H

#include "system.h"

/* Initialises the led mat rows and columns to off */
void init_led_mat (void);

/* Turns all the rows of the led mat off */
void rows_off (void);

/* Displays the ball on the led mat */
void display_ball (int ball_pos_col, int ball_pos_row);

/* Displays the player on the led mat */
void display_player (int player_pos);

#endif //DISPLAYER_H
