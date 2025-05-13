#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <cstdint>
#include <array>

#define ENGINE_DEPTH 8

struct Move {
    int value;
    int column;

    Move(int val = 0, int col = -1) : value(val), column(col) {}
};

class Engine {
public:
    Engine() = default;
    Move findBestMove(Game game, int depth);
private:
    Move minimax(Game game, int depth, int alpha, int beta, bool originalPlayer);
    int evaluate(Game game, bool turn);
};

#endif