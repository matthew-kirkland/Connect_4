#include "../include/game.h"
#include "../include/evaluate.h"

int evaluate(Game &game, bool turn) {
    std::array<std::array<int, NUM_COLS>, NUM_ROWS> evaluationTable = {{
        {3, 4, 5, 7, 5, 4, 3},
        {4, 6, 8, 10, 8, 6, 4},
        {5, 8, 11, 13, 11, 8, 5},
        {5, 8, 11, 13, 11, 8, 5},
        {4, 6, 8, 10, 8, 6, 4},
        {3, 4, 5, 7, 5, 4, 3}
    }};
    int score = 0;
    if (game.hasWon(turn)) {
        score += 1000;
    }
    if (game.hasWon(!turn)) {
        score -= 1000;
    }
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (turn == FIRST) {
                if ((game.p1Board >> (j + i * NUM_COLS)) & 1) {
                    score += evaluationTable[i][j];
                } else if ((game.p2Board >> (j + i * NUM_COLS)) & 1) {
                    score -= evaluationTable[i][j];
                }
            } else {
                if ((game.p2Board >> (j + i * NUM_COLS)) & 1) {
                    score += evaluationTable[i][j];
                } else if ((game.p1Board >> (j + i * NUM_COLS)) & 1) {
                    score -= evaluationTable[i][j];
                }
            }
        }
    }
    return score;
}