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

typedef struct game *Game;

struct game {
    uint64_t p1Board;
    uint64_t p2Board;
    int moveStack[MAX_MOVES];
    int moveCount;
    bool turn;
};

extern char tokens[];

Game initialiseGame();
void printBoard(Game game);
bool hasWonHorizontal(Game game, bool turn);
bool hasWonVertical(Game game, bool turn);
bool hasWonDiagonalTLBR(Game game, bool turn);
bool hasWonDiagonalBLTR(Game game, bool turn);
bool hasWon(Game game, bool turn);
void placeTile(Game game, int playerInput, int insertRow);
void gameLoop(Game game);
void undoMove(Game game);

#endif