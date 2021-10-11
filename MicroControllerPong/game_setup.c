/* Functions for game setup, displaying welcoming messages.
 * Written by Oliver Cranshaw and Sam McMillan for Ence260
 */

#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30


/* Sets the led_matrix to show an inputed char */
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


/* Initialise the tinygl module and set the game intro text on the led_matrix */
void start_text (void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("Welcome To Pong!");
}


/* Sets the led matrix to show the setup text */
void setup_text (void)
{
    tinygl_text("  Nav switch to set score limit.");
}
