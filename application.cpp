#include "include/game.h"
#include "include/engine.h"
#include "include/application.h"

void Application::run(Game game) {
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                break;
            }
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::KeyPressed::Scancode::Num1) {
                    game.placeTile(0, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::KeyPressed::Scancode::Num2) {
                    game.placeTile(1, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::KeyPressed::Scancode::Num3) {
                    game.placeTile(2, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::KeyPressed::Scancode::Num4) {
                    game.placeTile(3, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::KeyPressed::Scancode::Num5) {
                    game.placeTile(4, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::KeyPressed::Scancode::Num6) {
                    game.placeTile(5, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::KeyPressed::Scancode::Num7) {
                    game.placeTile(6, NUM_ROWS - 1);
                } else if (keyPressed->scancode == sf::KeyPressed::Scancode::U) {
                    game.undoMove();
                } else if (keyPressed->scancode == sf::KeyPressed:Scancode::H) {
                    Move bestMove = engine.findBestMove(game, ENGINE_DEPTH);
                    std::cout << "The best move for " << tokens[turn] << " is to play column " << bestMove.column + 1 << " (evaluation of " << bestMove.value << ")\n";
                } else if (keyPressed->scancode == sf::KeyPressed::Scancode::R) {
                    game.resetGame();
                } else {
                    std::cout << "Invalid key pressed\n";
                }
            }
            if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    game.placeTile(findColumn(mouseButtonPressed->position.x), NUM_ROWS - 1);
                }
            }
        }
        // if someone won or it was a draw, end the game loop
        if (game.hasWon(turn) || game.moveCount >= MAX_MOVES) {
            game.endGame();
        }
        window.clear(sf::Color::Black);
        window.draw(boardSprite);
        window.display();
    }
}

int Application::findColumn(int x) {
    if (x >= COL_1_START && x <= COL_1_END) return 1;
    if (x >= COL_2_START && x <= COL_2_END) return 2;
    if (x >= COL_3_START && x <= COL_3_END) return 3;
    if (x >= COL_4_START && x <= COL_4_END) return 4;
    if (x >= COL_5_START && x <= COL_5_END) return 5;
    if (x >= COL_6_START && x <= COL_6_END) return 6;
    if (x >= COL_7_START && x <= COL_7_END) return 7;
    else return -1;
}

int main() {
    Game game;
    Application application;
    application.run(game);
}
