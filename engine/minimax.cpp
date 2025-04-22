#include "../include/game.h"
#include "../include/evaluate.h"
#include "../include/minimax.h"

// TreeNode *createBranch(Game &game, int depth, bool turn) {
//     TreeNode *currentNode = new TreeNode();

//     if (depth == 0 || game.hasWon(turn) || game.hasWon(!turn)) {
//         currentNode->value = evaluate(game, turn);
//         return currentNode;
//     }

//     currentNode->value = 0;
//     for (int i = 0; i < NUM_COLS; i++) {
//         int tile = ((game.p1Board >> i) & 1) | ((game.p2Board >> i) & 1);
//         if (tile != 0) continue;

//         game.placeTile(i, NUM_ROWS - 1);
//         currentNode->children[i] = createBranch(game, depth - 1, turn);
//         game.undoMove();
//     }
//     return currentNode;
// }

// TreeNode *createTree(Game &game, int depth) {
//     return createBranch(game, depth, game.turn);
// }

// static inline bool isLeaf(TreeNode *node) {
//     for (int i = 0; i < NUM_COLS; i++) {
//         if (node->children[i] != NULL) {
//             return false;
//         }
//     }
//     return true;
// }

Move minimax(Game &game, int depth, bool isMax) {
    if (depth == 0 || game.hasWon(game.turn) || game.hasWon(!game.turn)) {
        return Move(evaluate(game), -1);
    }

    if (isMax) {
        Move bestMove(INT_MIN, -1);
        for (int i = 0; i < NUM_COLS; i++) {
            // play the move
            game.placeTile(i, NUM_ROWS - 1);
            // determine if the resulting move evaluation is better than teh current option
            Move childMove = minimax(game, depth - 1, false);
            if (childMove.value > bestMove.value) {
                bestMove.value = childMove.value;
                bestMove.column = childMove.column;
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
            Move childMove = minimax(game, depth - 1, true);
            if (childMove.value < bestMove.value) {
                bestMove.value = childMove.value;
                bestMove.column = childMove.column;
            }
            // undo the move
            game.undoMove();
        }
        return bestMove;
    }
}