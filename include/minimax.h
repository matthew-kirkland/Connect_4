#ifndef MINIMAX_H
#define MINIMAX_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <cstdint>

struct TreeNode {
    int value;
    TreeNode* children[NUM_COLS] = {nullptr};

    TreeNode() : value(0) {
        for (int i = 0; i < NUM_COLS; ++i) {
            children[i] = nullptr;
        }
    }
};

struct Move {
    int value;
    int column;

    Move(int val = 0, int col = -1) : value(val), column(col) {}
};

TreeNode *createBranch(Game &game, int depth, bool turn);
TreeNode *createTree(Game &game, int depth);
Move minimax(TreeNode *node, bool isMax);

#endif