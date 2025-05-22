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
        window.create(sf::VideoMode(sf::Vector2u(750, 645)), "Connect 4", sf::Style::Close);
        if (!boardTexture.loadFromFile("../assets/board.png") ||
            !redTokenTexture.loadFromFile("../assets/red_token.png") ||
            !yellowTokenTexture.loadFromFile("../assets/yellow_token.png") ||
            !tokenTexture.loadFromFile("../assets/token.png")) {
            std::cout << "Error loading one of the files\n";
        }
        window.setKeyRepeatEnabled(false);
    }
    void run(Game game);
private:
    sf::RenderWindow window;
    sf::Texture boardTexture;
    sf::Texture redTokenTexture;
    sf::Texture yellowTokenTexture;
    sf::Texture tokenTexture;

    int findColumn(int x) const;
    void drawToken(bool turn, int row, int col, int alpha);
};
