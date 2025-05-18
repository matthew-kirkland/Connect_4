#include "include/game.h"
#include "include/engine.h"
#include "include/application.h"

void Application::run(Game game) {
    sf::Sprite boardSprite(boardTexture);
    Engine engine;

    while (window.isOpen()) {
        // if someone won or it was a draw, end the game loop
        if ((game.hasWon(game.turn) || game.moveCount >= MAX_MOVES) && game.isActive) {
            game.endGame();
            std::cout << tokens[game.turn] << " has won!\n";
        }
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                break;
            }

            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
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
                    Move bestMove = engine.findBestMove(game, ENGINE_DEPTH);
                    std::cout << "The best move for " << tokens[game.turn] << " is to play column " << bestMove.column + 1 << " (evaluation of " << bestMove.value << ")\n";
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                    game.resetGame();
                } else {
                    std::cout << "Invalid key pressed\n";
                }
            }
            if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    game.placeToken(findColumn(mouseButtonPressed->position.x), NUM_ROWS - 1);
                }
            }
        }
        
        window.clear();
        window.draw(boardSprite);
        for (int i = 0; i < NUM_COLS; i++) {
            drawTokens(game, i);
        }
        window.display();
    }
}

// fix this to work with different window sizes
int Application::findColumn(int x) {
    if (x >= COL_1_START && x <= COL_1_END) return 0;
    if (x >= COL_2_START && x <= COL_2_END) return 1;
    if (x >= COL_3_START && x <= COL_3_END) return 2;
    if (x >= COL_4_START && x <= COL_4_END) return 3;
    if (x >= COL_5_START && x <= COL_5_END) return 4;
    if (x >= COL_6_START && x <= COL_6_END) return 5;
    if (x >= COL_7_START && x <= COL_7_END) return 6;
    else return -1;
}

void Application::drawTokens(Game game, int col) {
    for (int i = 0; i < NUM_ROWS; i++) {
        if ((game.p1Board >> (col + i * NUM_COLS)) & 1) {
            sf::Sprite redTokenSprite(redTokenTexture);
            redTokenSprite.setPosition({10 + 105 * col, 105 * i});
            window.draw(redTokenSprite);
        } else if ((game.p2Board >> (col + i * NUM_COLS)) & 1) {
            sf::Sprite yellowTokenSprite(yellowTokenTexture);
            yellowTokenSprite.setPosition({10 + 105 * col, 105 * i});
            window.draw(yellowTokenSprite);
        }
    }
}

int main() {
    Game game;
    Application application;
    application.run(game);
}
