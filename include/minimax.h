#ifndef MINIMAX_H
#define MINIMAX_H

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

struct node *createBranch(struct game *game, int currentHeight, int depth, bool turn);
struct node *createTree(struct game *game, int depth);
struct move minimax(struct node *node, bool isMax);

#endif