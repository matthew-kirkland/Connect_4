#include "../include/game.h"
#include "../include/evaluate.h"
#include "../include/minimax.h"

Move minimax(Game game, int depth, bool originalPlayer) {
    if (depth == 0 || game.hasWon(game.turn) || game.hasWon(!game.turn)) {
        return Move(evaluate(game, originalPlayer), -1);
    }
    bool isMax = (game.turn == originalPlayer);
    Move bestMove(isMax ? INT_MIN : INT_MAX, -1);
    for (int i = 0; i < NUM_COLS; i++) {
        if (game.columnFull(i)) continue;
        
        game.placeTile(i, NUM_ROWS - 1);
        Move childMove = minimax(game, depth - 1, originalPlayer);
        if ((isMax && childMove.value > bestMove.value) || (!isMax && childMove.value < bestMove.value)) {
            bestMove.value = childMove.value;
            bestMove.column = i;
        }
        game.undoMove();
    }
    return bestMove;
}