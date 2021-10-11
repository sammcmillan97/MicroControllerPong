#ifndef SCORE_HANDLER_H
#define SCORE_HANDLER_H

#include "system.h"

/* Sends a char to let other player know that this player has lost, then Displays a message letting player know they lost the point */
char handle_loss (int player_score);

/* Lets the other player know this player hasn't scored the max score, then displays a message letting the player know they won the point */
void handle_win (int player_score);

/* Displays the end game message letting the player know if they won or lost */
void end_game (bool lost);

#endif //SCORE_HANDLER_H
