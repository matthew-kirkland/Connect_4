#ifndef GAME_H
#define GAME_H

#define NUM_ROWS 6
#define NUM_COLS 7
#define NUM_TO_WIN 4

#define FIRST 0
#define SECOND 1

#define BLANK_TOKEN '_'
#define FIRST_TOKEN 'X'
#define SECOND_TOKEN 'O'

struct game {
    int turn;
    char **board;
};

extern char tokens[];

#endif