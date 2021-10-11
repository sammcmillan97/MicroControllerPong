/* Functions for displaying ball and player movement during game
 * Written by Oliver Cranshaw and Sam McMillan for Ence260
 */

#include "pio.h"

/* A list of the ledmat rows */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/* A list of the ledmat cols */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/* Initialises the led mat rows and columns to off */
void init_led_mat (void)
{
    for (int row = 0; row < LEDMAT_ROWS_NUM - 1;  row++) {
        pio_config_set(rows[row], PIO_OUTPUT_HIGH);
    }
    pio_config_set(rows[6], PIO_OUTPUT_LOW);

    for (int col = 0; col < LEDMAT_COLS_NUM; col++) {
        pio_config_set(cols[col], PIO_OUTPUT_HIGH);
    }
}

/* Turns all the rows of the led mat off */
void rows_off (void)
{

    for (int row = 0; row < LEDMAT_ROWS_NUM;  row++) {
        pio_output_high(rows[row]);
    }
}

/* Displays the ball on the led mat */
void display_ball (int ball_pos_col, int ball_pos_row)
{

    for (int col = 0; col < LEDMAT_COLS_NUM; col++) {

        if (col != ball_pos_col) {
            pio_output_high(cols[col]);
        }
    }

    for (int row = 0; row < LEDMAT_ROWS_NUM;  row++) {

        if (row != ball_pos_row) {
            pio_output_high(rows[row]);
        }
    }
    pio_output_low(cols[ball_pos_col]);
    pio_output_low(rows[ball_pos_row]);
}

/* Displays the player on the led mat */
void display_player (int player_pos)
{
    if (player_pos == 0) {
        rows_off();
        pio_output_high(cols[2]);
        pio_output_high(cols[3]);
        pio_output_high(cols[4]);
        pio_output_low(cols[0]);
        pio_output_low(cols[1]);

        pio_output_low(rows[6]);
    }

    if (player_pos == 1) {
        rows_off();
        pio_output_high(cols[0]);
        pio_output_high(cols[3]);
        pio_output_high(cols[4]);
        pio_output_low(cols[1]);
        pio_output_low(cols[2]);

        pio_output_low(rows[6]);
    }

    if (player_pos == 2) {
        rows_off();
        pio_output_high(cols[0]);
        pio_output_high(cols[1]);
        pio_output_high(cols[4]);
        pio_output_low(cols[2]);
        pio_output_low(cols[3]);

        pio_output_low(rows[6]);

    }
    if (player_pos == 3) {
        rows_off();
        pio_output_high(cols[0]);
        pio_output_high(cols[1]);
        pio_output_high(cols[2]);
        pio_output_low(cols[3]);
        pio_output_low(cols[4]);
        pio_output_low(rows[6]);
    }
}
