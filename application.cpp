#include "include/game.h"
#include "include/engine.h"
#include "include/application.h"

void Application::run(Game game) {
    sf::Sprite boardSprite(boardTexture);
    Engine engine;
    
    bool drawHint = false;
    Move bestMove;
    window.clear();
    while (window.isOpen()) {
        bool currentPlayer = game.turn;
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                drawHint = false;
                window.close();
                break;
            }

            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                drawHint = false;
                if (keyPressed->scancode == sf::Keyboard::Scancode::Num1) {
                    game.placeToken(0, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Num2) {
                    game.placeToken(1, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Num3) {
                    game.placeToken(2, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Num4) {
                    game.placeToken(3, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Num5) {
                    game.placeToken(4, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Num6) {
                    game.placeToken(5, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::Num7) {
                    game.placeToken(6, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::U) {
                    game.undoMove();
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::H) {
                    bestMove = engine.findBestMove(game, ENGINE_DEPTH);
                    drawHint = true;
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                    game.resetGame();
                } else {
                    drawHint = true;
                    std::cout << "Invalid key pressed\n";
                }
            }
            if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    drawHint = false;
                    game.placeToken(findColumn(mouseButtonPressed->position.x), NUM_ROWS - 1);
                }
            }
        }

        if ((game.hasWon(currentPlayer) || game.moveCount >= MAX_MOVES) && game.isActive) {
            game.endGame();
            std::cout << tokens[currentPlayer] << " has won!\n";
        }
        
        window.draw(boardSprite);
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if ((game.p1Board >> (j + i * NUM_COLS)) & 1) {
                    drawToken(FIRST, i, j, 255);
                } else if ((game.p2Board >> (j + i * NUM_COLS)) & 1) {
                    drawToken(SECOND, i, j, 255);
                }
            }
        }
        if (drawHint) {
            int row = game.getNextOpenRow(bestMove.column);
            if (row != -1) {
                drawToken(game.turn, game.getNextOpenRow(bestMove.column), bestMove.column, 128);
            }
        }
        window.display();
    }
}

// fix this to work with different window sizes
int Application::findColumn(int x) const {
    if (x >= COL_1_START && x <= COL_1_END) return 0;
    if (x >= COL_2_START && x <= COL_2_END) return 1;
    if (x >= COL_3_START && x <= COL_3_END) return 2;
    if (x >= COL_4_START && x <= COL_4_END) return 3;
    if (x >= COL_5_START && x <= COL_5_END) return 4;
    if (x >= COL_6_START && x <= COL_6_END) return 5;
    if (x >= COL_7_START && x <= COL_7_END) return 6;
    else return -1;
}

void Application::drawToken(bool turn, int row, int col, int alpha) {
    if (turn == FIRST) {
        sf::Sprite redTokenSprite(tokenTexture);
        redTokenSprite.setColor(sf::Color(255, 0, 0, alpha));
        redTokenSprite.setPosition({(float)(10 + 105 * col), (float)(105 * row)});
        window.draw(redTokenSprite);
    } else if (turn == SECOND) {
        sf::Sprite yellowTokenSprite(tokenTexture);
        yellowTokenSprite.setColor(sf::Color(255, 255, 0, alpha));
        yellowTokenSprite.setPosition({(float)(10 + 105 * col), (float)(105 * row)});
        window.draw(yellowTokenSprite);
    }
}

int main() {
    Game game;
    Application application;
    application.run(game);
}
