#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({750, 645}), "Connect 4", sf::Style::Default);
    sf::Texture boardTexture("assets/board.png");
    sf::Texture redTokenTexture("assets/red_token.png");
    sf::Texture yellowTokenTexture("assets/yellow_token.png");

    sf::Sprite boardSprite(boardTexture);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(boardSprite);
        window.display();
    }
}