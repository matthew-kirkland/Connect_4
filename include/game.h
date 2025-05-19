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

#define FIRST_TOKEN 'R'
#define SECOND_TOKEN 'Y'

extern char tokens[];

class Game {
public:
    uint64_t p1Board;
    uint64_t p2Board;
    int moveStack[MAX_MOVES];
    int moveCount;
    bool turn;
    bool isActive;
    Game() {
        p1Board = 0;
        p2Board = 0;
        moveCount = 0;
        turn = FIRST;
        isActive = true;
    }

    bool hasWon(bool who) const;
    bool columnFull(int col) const;
    void placeToken(int playerInput, int insertRow);
    void undoMove();
    void endGame();
    void resetGame();
    int getNextOpenRow(int col) const;

private:
    bool hasWonHorizontal(bool who) const;
    bool hasWonVertical(bool who) const;
    bool hasWonDiagonalTLBR(bool who) const;
    bool hasWonDiagonalBLTR(bool who) const;
};

#endif