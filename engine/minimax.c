#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "../include/game.h"
#include "../include/evaluate.h"
#include "../include/minimax.h"

TreeNode newNode() {
    TreeNode newNode = malloc(sizeof(struct node));
    newNode->value = 0;
    for (int i = 0; i < NUM_COLS; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

TreeNode createBranch(Game game, int depth, bool turn) {
    TreeNode currentNode = newNode();

    if (depth == 0) {
        currentNode->value = evaluate(game, turn);
        return currentNode;
    }
    if (hasWon(game, turn) || hasWon(game, !turn)) {
        currentNode->value = evaluate(game, turn);
        return currentNode;
    }

    currentNode->value = 0;
    for (int i = 0; i < NUM_COLS; i++) {
        if (game->board[0][i] != BLANK_TOKEN) continue;

        placeTile(game, i, NUM_ROWS - 1);
        currentNode->children[i] = createBranch(game, depth - 1, turn);
        undoMove(game);
    }
    return currentNode;
}

TreeNode createTree(Game game, int depth) {
    return createBranch(game, depth, game->turn);
}

static bool isLeaf(TreeNode node) {
    for (int i = 0; i < NUM_COLS; i++) {
        if (node->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

Move minimax(TreeNode node, bool isMax) {
    if (isLeaf(node)) {
        return (Move){ .value = node->value, .column = -1 };
    }

    Move bestMove;
    bestMove.value = isMax ? INT_MIN : INT_MAX;
    bestMove.column = -1;
    for (int i = 0; i < NUM_COLS; i++) {
        if (node->children[i] != NULL) {
            Move childMove = minimax(node->children[i], !isMax);
            if (isMax) {
                if (childMove.value > bestMove.value) {
                    bestMove.value = childMove.value;
                    bestMove.column = i;
                }
            } else {
                if (childMove.value < bestMove.value) {
                    bestMove.value = childMove.value;
                    bestMove.column = i;
                }
            }
        }
    }
    return bestMove;
}