#ifndef BALL_H
#define BALL_H

#include "system.h"

/* calculates and returns the horizontal direction of the ball after a hit */
char calc_hor_dir(int ball_pos_col, int player_pos);

/* Checks if the player has hit the ball and returns true if it has been hit, false otherwise. */
bool check_hit(int player_pos, int ball_pos_col);

/* Send a char to other player, each char represents a different column and ball direction */
void send_ball_over(int ball_pos_col, char ball_dir_hor);

/* Checks that the ball has been received correctly over IR */
bool recieve_ball_function(char ch);

/* Sets the column and direction of the received ball according to the received char */
int set_incoming_ball_col(char ch);

/* Sets the direction of the incoming ball according to the received char */
char set_incoming_ball_dir(char ch);

#endif //BALL_H
