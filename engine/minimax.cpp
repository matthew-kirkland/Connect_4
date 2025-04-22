#include "../include/game.h"
#include "../include/evaluate.h"
#include "../include/minimax.h"

Move minimax(Game game, int depth, bool originalPlayer) {
    if (depth == 0 || game.hasWon(game.turn) || game.hasWon(!game.turn)) {
        return Move(evaluate(game, originalPlayer), -1);
    }
    bool isMax = (game.turn == originalPlayer);
    if (isMax) {
        Move bestMove(INT_MIN, -1);
        for (int i = 0; i < NUM_COLS; i++) {
            // play the move
            game.placeTile(i, NUM_ROWS - 1);
            // determine if the resulting move evaluation is better than teh current option
            Move childMove = minimax(game, depth - 1, originalPlayer);
            if (childMove.value > bestMove.value) {
                bestMove.value = childMove.value;
                bestMove.column = i;
            }
            // undo the move
            game.undoMove();
        }
        return bestMove;
    } else {
        Move bestMove(INT_MAX, -1);
        for (int i = 0; i < NUM_COLS; i++) {
            // play the move
            game.placeTile(i, NUM_ROWS - 1);
            // determine if the resulting move evaluation is better than teh current option
            Move childMove = minimax(game, depth - 1, originalPlayer);
            if (childMove.value < bestMove.value) {
                bestMove.value = childMove.value;
                bestMove.column = i;
            }
            // undo the move
            game.undoMove();
        }
        return bestMove;
    }
}