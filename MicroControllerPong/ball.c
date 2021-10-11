/* Controls ball function in pong, Sends and recieves ball between players.
 * Written by Oliver Cranshaw and Sam McMillan for Ence260
 */

#include "ir_uart.h"


/* calculates and returns the horizontal direction of the ball after a hit */
char calc_hor_dir(int ball_pos_col, int player_pos)
{
    if (ball_pos_col == 0) {
        if (player_pos == 0) {
            return 'l';
        }
    }
    if (ball_pos_col == 1) {
        if (player_pos == 0) {
            return 'r';
        }
        if (player_pos == 1) {
            return 'l';
        }
    }
    if (ball_pos_col == 2) {
        if (player_pos == 1)
        {
            return 'r';
        }
        if (player_pos == 2) {
            return 'l';
        }
    }
    if (ball_pos_col == 3) {
        if (player_pos == 2) {
            return 'r';
        }
        if (player_pos == 3) {
            return 'l';
        }
    }
    if (ball_pos_col == 4) {
        if (player_pos == 3) {
            return 'r';
        }
    }
    return 'e';
}


/* Checks if the player has hit the ball and returns true if it has been hit, false otherwise. */
bool check_hit(int player_pos, int ball_pos_col)
{
    if ((player_pos == 0 && ball_pos_col == 2) | (player_pos == 0 && ball_pos_col == 3) | (player_pos == 0 && ball_pos_col == 4)){
        return false;
    }
    if ((player_pos == 1 && ball_pos_col == 0) | (player_pos == 1 && ball_pos_col == 3) | (player_pos == 1 && ball_pos_col == 4)) {
        return false;
    }
    if ((player_pos == 2 && ball_pos_col == 0) | (player_pos == 2 && ball_pos_col == 1) | (player_pos == 2 && ball_pos_col == 4)) {
        return false;
    }
    if ((player_pos == 3 && ball_pos_col == 0) | (player_pos == 3 && ball_pos_col == 1) | (player_pos == 3 && ball_pos_col == 2)) {
        return false;
    }

    return true;

}


/* Send a char to other player, each char represents a different column and ball direction */
void send_ball_over(int ball_pos_col, char ball_dir_hor)
{
    if (ball_pos_col == 0 && ball_dir_hor == 'l') {
        ir_uart_putc('A');
    }
    if (ball_pos_col == 0 && ball_dir_hor == 'r') {
        ir_uart_putc('B');
    }
    if (ball_pos_col == 1 && ball_dir_hor == 'l') {
        ir_uart_putc('C');
    }
    if (ball_pos_col == 1 && ball_dir_hor == 'r') {
        ir_uart_putc('D');
    }
    if (ball_pos_col == 2 && ball_dir_hor == 'l') {
        ir_uart_putc('E');
    }
    if (ball_pos_col == 2 && ball_dir_hor == 'r') {
        ir_uart_putc('F');
    }
    if (ball_pos_col == 3 && ball_dir_hor == 'l') {
        ir_uart_putc('G');
    }
    if (ball_pos_col == 3 && ball_dir_hor == 'r') {
        ir_uart_putc('H');
    }
    if (ball_pos_col == 4 && ball_dir_hor == 'l') {
        ir_uart_putc('I');
    }
    if (ball_pos_col == 4 && ball_dir_hor == 'r') {
        ir_uart_putc('J');
    }
}


/* Checks that the ball has been received correctly over IR */
bool recieve_ball_function(char ch)
{
    bool recieved = false;

    if ((ch == 'A') | (ch == 'B') | (ch == 'C') | (ch == 'D') | (ch == 'E') | (ch == 'F') | (ch == 'G') | (ch == 'H') | (ch == 'I') | (ch == 'J'))
    {
        recieved = true;
    }

    return recieved;

}


/* Sets the column of the received ball according to the received char */
int set_incoming_ball_col(char ch)
{
    int ball_pos_col;

    if (ch == 'A') {
        ball_pos_col = 4;
    }
    if (ch == 'B') {
        ball_pos_col = 4;
    }
    if (ch == 'C') {
        ball_pos_col = 3;
    }
    if (ch == 'D') {
        ball_pos_col = 3;
    }
    if (ch == 'E') {
        ball_pos_col = 2;
    }
    if (ch == 'F') {
        ball_pos_col = 2;
    }
    if (ch == 'G') {
        ball_pos_col = 1;
    }
    if (ch == 'H') {
        ball_pos_col = 1;
    }
    if (ch == 'I') {
        ball_pos_col = 0;
    }
    if (ch == 'J') {
        ball_pos_col = 0;
    }

    return ball_pos_col;

}


/* Sets the direction of the incoming ball according to the received char */
char set_incoming_ball_dir(char ch)
{
    char ball_dir_hor;
    if (ch == 'A') {
        ball_dir_hor = 'r';
    }
    if (ch == 'B') {
        ball_dir_hor = 'l';
    }
    if (ch == 'C') {
        ball_dir_hor = 'r';
    }
    if (ch == 'D') {
        ball_dir_hor = 'l';
    }
    if (ch == 'E') {
        ball_dir_hor = 'r';
    }
    if (ch == 'F') {
        ball_dir_hor = 'l';
    }
    if (ch == 'G') {
        ball_dir_hor = 'r';
    }
    if (ch == 'H') {
        ball_dir_hor = 'l';
    }
    if (ch == 'I') {
        ball_dir_hor = 'r';
    }
    if (ch == 'J') {
        ball_dir_hor = 'l';
    }

    return ball_dir_hor;

}
