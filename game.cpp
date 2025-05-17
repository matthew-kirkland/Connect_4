#include "include/game.h"
#include "include/engine.h"

char tokens[] = {FIRST_TOKEN, SECOND_TOKEN};

bool Game::hasWonHorizontal(bool who) const {
    uint64_t board = (who == FIRST) ? p1Board : p2Board;
    uint64_t preventWrapMask = 0x78F1E3C78F;
    uint64_t check = (board & (board >> 1) & (board >> 2) & (board >> 3)) & preventWrapMask;
    return check != 0;
}

bool Game::hasWonVertical(bool who) const {
    uint64_t board = (who == FIRST) ? p1Board : p2Board;
    uint64_t preventWrapMask = 0x1FFFFF;
    uint64_t check = (board & (board >> NUM_COLS) & (board >> NUM_COLS * 2) & (board >> NUM_COLS * 3)) & preventWrapMask;
    return check != 0;
}

bool Game::hasWonDiagonalTLBR(bool who) const {
    uint64_t board = (who == FIRST) ? p1Board : p2Board;
    uint64_t preventWrapMask = 0x3C78F;
    uint64_t check = (board & (board >> 8) & (board >> 16) & (board >> 24)) & preventWrapMask;
    return check != 0;
}

bool Game::hasWonDiagonalBLTR(bool who) const {
    uint64_t board = (who == FIRST) ? p1Board : p2Board;
    uint64_t preventWrapMask = 0x1E3C78;
    uint64_t check = (board & (board >> 6) & (board >> 12) & (board >> 18)) & preventWrapMask;
    return check != 0;
}

bool Game::hasWon(bool who) const {
    return (hasWonHorizontal(who) ||
            hasWonVertical(who) ||
            hasWonDiagonalTLBR(who) ||
            hasWonDiagonalBLTR(who));
}

bool Game::columnFull(int col) const {
    return (((p1Board >> col) & 1) | ((p2Board >> col) & 1));
}

void Game::placeToken(int playerInput, int insertRow) {
    if (insertRow < 0) return;

    int tile = ((p1Board >> (playerInput + insertRow * NUM_COLS)) & 1) | ((p2Board >> (playerInput + insertRow * NUM_COLS)) & 1);
    if (tile != 0) {
        placeToken(playerInput, insertRow - 1);
    } else {
        uint64_t mask = 1;
        uint64_t boardBit = mask << (playerInput + insertRow * NUM_COLS);
        if (turn == FIRST) {
            p1Board |= boardBit;
        } else {
            p2Board |= boardBit;
        }
        moveStack[moveCount] = playerInput;
        moveCount++;
        turn = !turn;
    }
}

void Game::undoMove() {
    moveCount--;
    turn = !turn;
    int column = moveStack[moveCount];
    uint64_t mask = 1;
    for (int i = 0; i < NUM_ROWS; i++) {
        if (turn == FIRST) {
            if ((p1Board >> (column + i * NUM_COLS)) & 1) {
                p1Board ^= (mask << (column + i * NUM_COLS));
                break;
            }
        } else {
            if ((p2Board >> (column + i * NUM_COLS)) & 1) {
                p2Board ^= (mask << (column + i * NUM_COLS));
                break;
            }
        }
    }
}

void Game::endGame() {
    isActive = false;
}

void Game::resetGame() {
    p1Board = 0;
    p2Board = 0;
    moveCount = 0;
    turn = FIRST;
    isActive = true;
    for (int i = 0; i < MAX_MOVES; i++) {
        moveStack[i] = -1;
    }
}
