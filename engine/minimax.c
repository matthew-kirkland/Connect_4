#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include "../include/game.h"
#include "../include/evaluate.h"

struct node {
    int value;
    struct node *children[NUM_COLS];
};

struct move {
    int value;
    int column;
};

struct node *newNode() {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->value = 0;
    for (int i = 0; i < NUM_COLS; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

struct node *createBranch(struct game *game, int currentHeight, int depth, bool turn) {
    struct node *currentNode = newNode();

    if (currentHeight == depth) {
        currentNode->value = evaluate(game, turn);
        return currentNode;
    }

    currentNode->value = 0;
    for (int i = 0; i < NUM_COLS; i++) {
        if (game->board[0][i] != BLANK_TOKEN) continue;

        placeTile(game, i, NUM_ROWS - 1);
        currentNode->children[i] = createBranch(game, currentHeight + 1, depth, !turn);
        undoMove(game);
    }
    return currentNode;
}

struct node *createTree(struct game *game, int depth) {
    return createBranch(game, 0, depth, game->turn);
}

struct move minimax(struct node *node, bool isMax) {
    if (isLeaf(node)) {
        return (struct move){ .value = node->value, .column = -1 };
    }

    struct move bestMove;
    bestMove.value = isMax ? INT_MIN : INT_MAX;
    bestMove.column = -1;
    for (int i = 0; i < NUM_COLS; i++) {
        if (node->children[i] != NULL) {
            int childMove = minimax(node->children[i], !isMax);
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

static bool isLeaf(struct node *node) {
    for (int i = 0; i < NUM_COLS; i++) {
        if (node->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static int min(int a, int b) {
    return (a < b) ? a : b;
}