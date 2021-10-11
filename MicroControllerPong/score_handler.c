/* Functions for handling and displaying score.
 * Written by Oliver Cranshaw and Sam McMillan for Ence260
 */

#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30

/* Sends a char to let other player know that this player has lost, then Displays a message letting player know they lost the point */
char handle_loss (int player_score)
{
    ir_uart_putc('L');
    char ch;
    ch = ir_uart_getc();

    if (ch != 'V') {
        char player_score_char = player_score + '0';
        char* msg = " Loss Score:  ";
        msg[13] = player_score_char;
        tinygl_draw_message(msg, tinygl_point (0, 0), 1);
        pacer_init (PACER_RATE);
        int i = 0;

        while (i < 3500) {
            pacer_wait();
            tinygl_update();
            i++;
        }
    }

    return ch;

}


/* Lets the other player know this player hasn't scored the max score, then displays a message letting the player know they won the point */
void handle_win (int player_score)
{
    ir_uart_putc('N');
    int j = 0;

    while (j < 2000) {
        j++;
    }
    char player_score_char = player_score + '0';
    char* msg =" Win Score:  ";
    msg[12] = player_score_char;
    tinygl_draw_message(msg, tinygl_point (0, 0), 1);
    pacer_init (PACER_RATE);
    int i = 0;

    while (i < 3500) {
        pacer_wait();
        tinygl_update();
        i++;
    }
}

/* Displays the end game message letting the player know if they won or lost */
void end_game (bool lost)
{
    if (lost) {
        tinygl_text("You lost! Better luck next time.");
    } else {
        tinygl_text("You won! Congratulations.");
    }
    pacer_init (PACER_RATE);
    int i = 0;

    while (i < 6000) {
        pacer_wait();
        tinygl_update();
        i++;
    }
    tinygl_clear();
    tinygl_update();
}
