#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#define COL_1_START 10
#define COL_1_END 109
#define COL_2_START 115
#define COL_2_END 214
#define COL_3_START 220
#define COL_3_END 319
#define COL_4_START 325
#define COL_4_END 424
#define COL_5_START 430
#define COL_5_END 529
#define COL_6_START 535
#define COL_6_END 634
#define COL_7_START 640
#define COL_7_END 739

class Application {
public:
    Application() {
        window.setKeyRepeatEnabled(false);
    }
    void run(Game game);
private:
    sf::RenderWindow window(sf::VideoMode({750, 645}), "Connect 4", sf::Style::Default);
    sf::Texture boardTexture("assets/board.png");
    sf::Texture redTokenTexture("assets/red_token.png");
    sf::Texture yellowTokenTexture("assets/yellow_token.png");

    sf::Sprite boardSprite(sf::Texture boardTexture("assets/board.png"));
    sf::Sprite redTokenSprite(sf::Texture redTokenTexture("assets/red_token.png"));
    sf::Sprite yellowTokenSprite(sf::Texture yellowTokenTexture("assets/yellow_token.png"));

    int findColumn(int x);
};
