#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <cstdint>
#include <array>

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
Move minimax(Game game, int depth, int alpha, int beta, bool originalPlayer);
int evaluate(Game game, bool turn);

#endif