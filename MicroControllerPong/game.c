/* Main function for running game.
 * Written by Oliver Cranshaw and Sam McMillan for Ence260
 */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pio.h"
#include "game_setup.h"
#include "ball.h"
#include "displayer.h"
#include "score_handler.h"

//Defining the pacer rate in hz and the message rate.
#define PACER_RATE 500
#define MESSAGE_RATE 30

//Defining the directions of the ball which are held as chars
#define BALL_LEFT 'l'
#define BALL_RIGHT 'r'
#define BALL_UP 'u'
#define BALL_DOWN 'd'

int main (void)
{
    system_init();
    ir_uart_init ();
    pacer_init (PACER_RATE);
    start_text();
    bool game_intro = true;

    while (game_intro) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            game_intro = false;
        }
    }
    setup_text();
    bool game_setup_text = true;

    while (game_setup_text) {
        pacer_wait();
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_NORTH) |  navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            game_setup_text = false;
        }
    }
    bool start_player = false;
    char max_score_char = '1';
    bool game_setup = true;

    while (game_setup) {
        pacer_wait();
        display_character(max_score_char);
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            max_score_char += 1;

            if (max_score_char > 55) { //Prevents max score from being higher than 7
                max_score_char = 55;
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            max_score_char -= 1;

            if (max_score_char < 49) { //Prevents max score from being less than 1
                max_score_char = 49;
            }
        }

        if (navswitch_down_p(NAVSWITCH_PUSH)) {
            ir_uart_putc(max_score_char);
            tinygl_clear();
            tinygl_update();
            char ch;
            ch = ir_uart_getc ();

            if (ch == 'A') {
                start_player = true;
                game_setup = false;
            }
        }

        if (ir_uart_read_ready_p()) {
            char ch;
            ch = ir_uart_getc ();

            if (ch == max_score_char) {
                ir_uart_putc('A');
                game_setup = false;
            } else {
                ir_uart_putc(BALL_RIGHT);
            }
        }
    }
    tinygl_clear();
    init_led_mat();

    int player_pos = 1; //Your player's position on the bottom row of the led matrix
    int player_score = 0; //Your score
    int max_score = max_score_char - '0'; //The chosen max score converted to a integer
    int ball_pos_row = 0; //The row of the led matrix that the ball is in
    int ball_pos_col = 2; //The column of the led matrix that the ball is in
    char ball_ver_dir = BALL_DOWN; //Setting the initial horizontal direction of the ball to down
    char ball_hor_dir = BALL_RIGHT; //Setting the initial vertical direction of the ball to right
    int ball_speed = 250; //Lower = faster
    int ball_speed_count = 0; //Counted during each of the main game loop up until ball speed, ball moves when count = speed
    bool ball_on_side = false; //Boolean value, true means the ball is on your led matrix, false otherwise
    bool lost = false; //Boolean that holds state of the game, if true game ends with this player as loser
    bool toggle = true; //Is toggled during every loop of the main function to display the ball and player properly

    if (start_player) {
        ball_on_side = true;
    }

    while (player_score < max_score && !lost) {
        pacer_wait();
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            player_pos += 1;

            if (player_pos > 3) {
                player_pos = 3;
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            player_pos -= 1;

            if (player_pos < 0) {
                player_pos = 0;
            }
        }

        if (toggle) {
            display_player(player_pos);
            toggle = false;
        } else {

            if (ball_on_side)  {
                display_ball(ball_pos_col, ball_pos_row);
            } else {
                char ch;
                ch = ir_uart_getc ();

                if (ch == 'L') {
                    player_score++;

                    if (player_score == max_score) {
                        ir_uart_putc('V');
                    } else {
                        handle_win(player_score);
                        ball_speed = 250;
                    }
                }

                if (recieve_ball_function(ch)) {
                    ball_pos_col = set_incoming_ball_col(ch);
                    ball_hor_dir = set_incoming_ball_dir(ch);
                    ball_on_side = true;
                }
            }
            toggle = true;
        }

        if (ball_speed_count == ball_speed && ball_on_side) {

            if (ball_pos_row == 5) {
                bool check = check_hit(player_pos, ball_pos_col);

                if (!check) {

                    char ch;
                    ch = handle_loss(player_score);

                    if (ch == 'V') {
                        lost = true;
                    }
                    ball_pos_row = 0;
                    ball_pos_col = 2;
                    ball_ver_dir = BALL_DOWN;
                    ball_hor_dir = BALL_RIGHT;
                    ball_speed = 250;
                } else {
                    ball_speed -= 35;

                    if (ball_speed < 35) {
                        ball_speed = 35;
                    }
                    ball_ver_dir = BALL_UP;
                    ball_hor_dir = calc_hor_dir(ball_pos_col, player_pos);
                }
            }

            if (ball_ver_dir == BALL_DOWN) {
                ball_pos_row += 1;
            } else {
                ball_pos_row -= 1;

                if (ball_pos_row == -1) {
                    send_ball_over(ball_pos_col, ball_hor_dir);
                    ball_ver_dir = BALL_DOWN;
                    ball_pos_row = 0;
                    ball_on_side = false;
                }
            }

            if (ball_hor_dir == BALL_RIGHT) {
                ball_pos_col += 1;

                if (ball_pos_col == 4) {
                    ball_hor_dir = BALL_LEFT;
                }
            } else if (ball_hor_dir == BALL_LEFT) {
                ball_pos_col -= 1;

                if (ball_pos_col == 0) {
                    ball_hor_dir = BALL_RIGHT;
                }
            }
            ball_speed_count = 0;
        }
        ball_speed_count++;
    }
    end_game(lost);

    return 0;

}
