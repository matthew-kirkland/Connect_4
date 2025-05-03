#include "include/game.h"
#include "include/engine.h"

int evaluate(Game game, bool turn) {
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

Move minimax(Game game, int depth, int alpha, int beta, bool originalPlayer) {
    if (depth == 0 || game.hasWon(game.turn) || game.hasWon(!game.turn) || game.moveCount >= MAX_MOVES) {
        return Move(evaluate(game, originalPlayer), -1);
    }
    bool isMax = (game.turn == originalPlayer);
    Move bestMove(isMax ? INT_MIN : INT_MAX, -1);
    for (int i = 0; i < NUM_COLS; i++) {
        if (game.columnFull(i)) continue;

        game.placeTile(i, NUM_ROWS - 1);
        Move childMove = minimax(game, depth - 1, alpha, beta, originalPlayer);
        game.undoMove();
        if ((isMax && childMove.value > bestMove.value) || (!isMax && childMove.value < bestMove.value)) {
            bestMove.value = childMove.value;
            bestMove.column = i;
        }
        if (isMax) {
            if (bestMove.value >= beta) break;
            alpha = std::max(alpha, bestMove.value);
        } else {
            if (bestMove.value <= alpha) break;
            beta = std::min(beta, bestMove.value);
        }
    }
    return bestMove;
}
