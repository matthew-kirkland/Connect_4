#ifndef GAME_H
#define GAME_H

#define NUM_ROWS 6
#define NUM_COLS 7
#define NUM_TO_WIN 4

#define MAX_MOVES 42

#define FIRST false
#define SECOND true

#define BLANK_TOKEN '_'
#define FIRST_TOKEN 'X'
#define SECOND_TOKEN 'O'

struct game {
    char **board;
    int moveStack[42];
    int moveCount;
    bool turn;
};

extern char tokens[];

struct game *initialiseGame();
void printBoard(struct game *game);
bool hasWonHorizontal(struct game *game, bool turn);
bool hasWonVertical(struct game *game, bool turn);
bool hasWonDiagonalTLBR(struct game *game, bool turn);
bool hasWonDiagonalBLTR(struct game *game, bool turn);
bool hasWon(struct game *game, bool turn);
void placeTile(struct game *game, int playerInput, int insertRow);
void gameLoop(struct game *game);
void undoMove(struct game *game);

#endif