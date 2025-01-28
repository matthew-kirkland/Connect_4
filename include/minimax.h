#ifndef MINIMAX_H
#define MINIMAX_H

#include "../include/game.h"
#include "../include/evaluate.h"

typedef struct node *TreeNode;
typedef struct move Move;

struct node {
    int value;
    struct node *children[NUM_COLS];
};

struct move {
    int value;
    int column;
};

TreeNode createBranch(Game game, int depth, bool turn);
TreeNode createTree(Game game, int depth);
Move minimax(TreeNode node, bool isMax);

#endif