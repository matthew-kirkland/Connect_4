#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

#include "include/game.h"
#include "include/minimax.h"

char tokens[] = {FIRST_TOKEN, SECOND_TOKEN};

void checkMalloc(void *item) {
    if (item == NULL) {
        fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
    }
}

void clearScreen() {
    const char *CLEAR_SCREEN_ANSI = "\033[1;1H\033[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, strlen(CLEAR_SCREEN_ANSI));
    fflush(stdout);
}

Game initialiseGame() {
    Game newGame = malloc(sizeof(struct game));
    checkMalloc(newGame);
    newGame->p1Board = 0;
    newGame->p2Board = 0;
    newGame->moveCount = 0;
    newGame->turn = FIRST;
    return newGame;
}

void printBoard(Game game) {
    // clearScreen();
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if ((game->p1Board >> (i * NUM_COLS + j)) & 1) printf("\033[31m%c \033[0m", tokens[FIRST]);
            else if ((game->p2Board >> (i * NUM_COLS + j)) & 1) printf("\033[33m%c \033[0m", tokens[SECOND]);
            else printf("%c ", BLANK_TOKEN);
        }
        printf("\n");
    }
}

bool hasWonHorizontal(Game game, bool turn) {
    uint64_t board = (turn == FIRST) ? game->p1Board : game->p2Board;
    uint64_t preventWrapMask = 0x78F1E3C78F;
    uint64_t check = (board & (board >> 1) & (board >> 2) & (board >> 3)) & preventWrapMask;
    return check != 0;
}

bool hasWonVertical(Game game, bool turn) {
    uint64_t board = (turn == FIRST) ? game->p1Board : game->p2Board;
    uint64_t preventWrapMask = 0x1FFFFF;
    uint64_t check = (board & (board >> NUM_COLS) & (board >> NUM_COLS * 2) & (board >> NUM_COLS * 3)) & preventWrapMask;
    return check != 0;
}

bool hasWonDiagonalTLBR(Game game, bool turn) {
    uint64_t board = (turn == FIRST) ? game->p1Board : game->p2Board;
    uint64_t preventWrapMask = 0x3C78F;
    uint64_t check = (board & (board >> 8) & (board >> 16) & (board >> 24)) & preventWrapMask;
    return check != 0;
}

bool hasWonDiagonalBLTR(Game game, bool turn) {
    uint64_t board = (turn == FIRST) ? game->p1Board : game->p2Board;
    uint64_t preventWrapMask = 0x1E3C78;
    uint64_t check = (board & (board >> 6) & (board >> 12) & (board >> 18)) & preventWrapMask;
    return check != 0;
}

bool hasWon(Game game, bool turn) {
    return (hasWonHorizontal(game, turn) ||
            hasWonVertical(game, turn) ||
            hasWonDiagonalTLBR(game, turn) ||
            hasWonDiagonalBLTR(game, turn));
}

void placeTile(Game game, int playerInput, int insertRow) {
    if (insertRow < 0) return;

    int tile = ((game->p1Board >> (playerInput + insertRow * NUM_COLS)) & 1) | ((game->p2Board >> (playerInput + insertRow * NUM_COLS)) & 1);
    if (tile != 0) {
        placeTile(game, playerInput, insertRow - 1);
    } else {
        uint64_t mask = 1;
        uint64_t boardBit = mask << (playerInput + insertRow * NUM_COLS);
        if (game->turn == FIRST) {
            game->p1Board |= boardBit;
        } else {
            game->p2Board |= boardBit;
        }
        game->moveStack[game->moveCount] = playerInput;
        game->moveCount++;
        game->turn = !game->turn;
    }
}

void undoMove(Game game) {
    if (game->moveCount > 0) {
        game->turn = !game->turn;
        game->moveCount--;
        int column = game->moveStack[game->moveCount];
        uint64_t mask = 1;
        for (int i = 0; i < NUM_ROWS; i++) {
            if (game->turn == FIRST) {
                if ((game->p1Board >> (column + i * NUM_COLS)) & 1) {
                    game->p1Board ^= (mask << (column + i * NUM_COLS));
                    break;
                }
            } else {
                if ((game->p2Board >> (column + i * NUM_COLS)) & 1) {
                    game->p2Board ^= (mask << (column + i * NUM_COLS));
                    break;
                }
            }
        }
    }
}

void gameLoop(Game game) {
    printBoard(game);
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') continue;
        if (c == 'q') {
            printf("Quitting!\n");
            break;
        }
        if (c == 'w') {
            printf("It is %c's turn\n", tokens[game->turn]);
            continue;
        }
        if (c == 'u') {
            undoMove(game);
            printBoard(game);
            continue;
        }
        if (c == 'h') {
            TreeNode gameTree = createTree(game, 6);
            Move bestMove = minimax(gameTree, true);
            printf("The best move for %c is to play column %d (evaluation of %d)\n", tokens[game->turn], bestMove.column + 1, bestMove.value);
            continue;
        }

        c = c - '0' - 1;
        if (c < 0 || c > NUM_COLS - 1) {
            printBoard(game);
            continue;
        }

        placeTile(game, c, NUM_ROWS - 1);
        if (hasWon(game, !game->turn)) {
            printBoard(game);
            printf("%c has won!\n", tokens[!game->turn]);
            break;
        }
        if (game->moveCount >= MAX_MOVES) {
            printBoard(game);
            printf("It's a draw!\n");
            break;
        }
        printBoard(game);
    }
    printf("Game ended!\n");
}

int main() {
    Game game = initialiseGame();
    gameLoop(game);
}
