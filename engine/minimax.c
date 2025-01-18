#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "../include/game.h"
#include "../include/evaluate.h"

struct node {
    int value;
    struct node *children[NUM_COLS];
};

struct node *createTree(struct game *game, int depth) {
    struct node *head = newNode();
    for (int i = 0; i < NUM_COLS; i++) {
        if (game->board[0][i] != BLANK_TOKEN) continue;
        head->children[i] = createBranch(game, 0, depth, i);
    }
    return head;
}

struct node *createBranch(struct game *game, int currentHeight, int depth, int column) {
    if (currentHeight == depth) return;
    placeTile(game, column, NUM_ROWS - 1);
    struct node *currentNode = newNode();
    currentNode->value = evaluate(game);
    for (int i = 0; i < NUM_COLS; i++) {
        if (game->board[0][i] != BLANK_TOKEN) continue;
        currentNode->children[i] = createBranch(game, currentHeight + 1, depth, i);
    }
    undoMove(game);
    return currentNode;
}

struct node *newNode() {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->value = 0;
    for (int i = 0; i < NUM_COLS; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

int minimax(int depth, ) {

}