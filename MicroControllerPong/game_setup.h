#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include "system.h"

/* Sets the led_matrix to show an inputed char */
void display_character (char character);


/* Initialise the tinygl module and set the game intro text on the led_matrix */
void start_text (void);

/* Sets the led matrix to show the setup text */
void setup_text (void);

#endif //GAME_SETUP_H
