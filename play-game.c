#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_ROWS 6
#define NUM_COLS 7
#define NUM_TO_WIN 4

#define FIRST 0
#define SECOND 1

#define BLANK_TOKEN '_'
#define FIRST_TOKEN 'X'
#define SECOND_TOKEN 'O'

struct game {
    int turn;
    char **board;
};

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

struct game *initialiseGame() {
    struct game *newGame = malloc(sizeof(struct game));
    checkMalloc(newGame);
    newGame->turn = FIRST;
    newGame->board = malloc(sizeof(char *) * NUM_ROWS);
    for (int i = 0; i < NUM_ROWS; i++) {
        newGame->board[i] = malloc(sizeof(char) * NUM_COLS);
        for (int j = 0; j < NUM_COLS; j++) {
            newGame->board[i][j] = BLANK_TOKEN;
        }
    }
    return newGame;
}

void printBoard(struct game *game) {
    clearScreen();
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%c ", game->board[i][j]);
        }
        printf("\n");
    }
}

bool hasWonHorizontal(struct game *game) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (NUM_COLS - j < NUM_TO_WIN) break;

            char t0 = game->board[i][j];
            if (t0 != tokens[game->turn]) continue;

            char t1 = game->board[i][j + 1];
            char t2 = game->board[i][j + 2];
            char t3 = game->board[i][j + 3];
            if (t0 == t1 && t0 == t2 && t0 == t3) {
                return true;
            }
        }
    }
    return false;
}

bool hasWonVertical(struct game *game) {
    for (int j = 0; j < NUM_COLS; j++) {
        for (int i = 0; i < NUM_ROWS; i++) {
            if (NUM_ROWS - i < NUM_TO_WIN) break;

            char t0 = game->board[i][j];
            if (t0 != tokens[game->turn]) continue;

            char t1 = game->board[i + 1][j];
            char t2 = game->board[i + 2][j];
            char t3 = game->board[i + 3][j];
            if (t0 == t1 && t0 == t2 && t0 == t3) {
                return true;
            }
        }
    }
    return false;
}

bool hasWonDiagonalTLBR(struct game *game) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (NUM_COLS - j < NUM_TO_WIN ||
                NUM_ROWS - i < NUM_TO_WIN) break;

            char t0 = game->board[i][j];
            if (t0 != tokens[game->turn]) continue;

            char t1 = game->board[i + 1][j + 1];
            char t2 = game->board[i + 2][j + 2];
            char t3 = game->board[i + 3][j + 3];
            if (t0 == t1 && t0 == t2 && t0 == t3) {
                return true;
            }
        }
    }
    return false;
}

bool hasWonDiagonalBLTR(struct game *game) {
    for (int i = NUM_ROWS - 1; i >= 0; i--) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (NUM_COLS - j < NUM_TO_WIN ||
                i < NUM_TO_WIN - 1) break;
            
            char t0 = game->board[i][j];
            if (t0 != tokens[game->turn]) continue;

            char t1 = game->board[i - 1][j + 1];
            char t2 = game->board[i - 2][j + 2];
            char t3 = game->board[i - 3][j + 3];
            if (t0 == t1 && t0 == t2 && t0 == t3) {
                return true;
            }
        }
    }
    return false;
}

bool hasWon(struct game *game) {
    return (hasWonHorizontal(game) ||
            hasWonVertical(game) ||
            hasWonDiagonalTLBR(game) ||
            hasWonDiagonalBLTR(game));
}

void placeTile(struct game *game, char playerInput, int insertRow) {
    if (insertRow < 0) return;

    if (game->board[insertRow][playerInput] != BLANK_TOKEN) {
        placeTile(game, playerInput, insertRow - 1);
    } else {
        game->board[insertRow][playerInput] = tokens[game->turn];
    }
}

void gameLoop(struct game *game) {
    printBoard(game);
    char c;
    while ((c = getchar()) != EOF) {
        if (c == 'q') {
            printf("Quitting!\n");
            break;
        }

        c = c - '0' - 1;
        if (c < 0 || c > NUM_COLS - 1) {
            printBoard(game);
            continue;
        }

        placeTile(game, c, NUM_ROWS - 1);
        if (hasWon(game)) {
            printBoard(game);
            printf("%c has won!", tokens[game->turn]);
            break;
        }

        // game->turn != game->turn;
        if (game->turn == FIRST) {
            game->turn = SECOND;
        } else {
            game->turn = FIRST;
        }
        printBoard(game);
    }
}

int main() {
    struct game *game = initialiseGame();
    gameLoop(game);
}