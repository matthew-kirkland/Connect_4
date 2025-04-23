#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <unistd.h>

#define NUM_ROWS 6
#define NUM_COLS 7
#define NUM_TO_WIN 4

#define MAX_MOVES 42

#define FIRST false
#define SECOND true

#define BLANK_TOKEN '_'
#define FIRST_TOKEN 'X'
#define SECOND_TOKEN 'O'

extern char tokens[];

class Game {
public:
    uint64_t p1Board;
    uint64_t p2Board;
    int moveStack[MAX_MOVES];
    int moveCount;
    bool turn;
    Game() {
        p1Board = 0;
        p2Board = 0;
        moveCount = 0;
        turn = FIRST;
    }

    void clearScreen() const;
    void printBoard() const;
    bool hasWonHorizontal(bool who) const;
    bool hasWonVertical(bool who) const;
    bool hasWonDiagonalTLBR(bool who) const;
    bool hasWonDiagonalBLTR(bool who) const;
    bool hasWon(bool who) const;
    bool columnFull(int col) const;
    void placeTile(int playerInput, int insertRow);
    void undoMove();
    void gameLoop();
};

#endif