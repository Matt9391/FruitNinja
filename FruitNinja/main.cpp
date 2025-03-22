#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Fruit.h"
#include "Functions.h"
#include "Random.h"
#include "Slash.h"
#include "Bomb.h"
#include "HalfFruit.h"
#include "UI.h"
#include "Menu.h"

std::vector<HalfFruit> halfFruits;
std::vector<Fruit> fruits;
std::vector<Bomb> bombs;
int scene = 0;

int main()
{    
    Random::Init();
    int frameCount = 0;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fruit Ninja");
    window.setFramerateLimit(60);
    //float radius = 25.f;  // Raggio del frutto
    
    //sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), 500);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    //sf::Vector2f sp(10, 25);
    //Fruit fruit(spawnPos, sp, radius, window);

    
    //fruits.push_back(fruit);

    std::vector<sf::Texture> textures;
    std::vector<std::string> texturesPaths = {
        "./Sprites/orange.png",
        "./Sprites/orangeTop.png",
        "./Sprites/orangeBottom.png",
        "./Sprites/peach.png",
        "./Sprites/peachTop.png",
        "./Sprites/peachBottom.png",
        "./Sprites/watermelon.png",
        "./Sprites/watermelonTop.png",
        "./Sprites/watermelonBottom.png",
        "./Sprites/plum.png",
        "./Sprites/background.png",
        "./Sprites/heart.png"
    };

    for (const auto& path : texturesPaths) {
        sf::Texture txt;
        if (txt.loadFromFile(path)) {
            textures.push_back(std::move(txt));
        }
        else {
            std::cerr << "errore nell'import delle immagine";
        }
    }

    UI::init(window, textures[textures.size() -1]);
    Menu::init(window);

    sf::Sprite background;
    sf::Texture& bgTxt = textures[textures.size() - 2];
    background.setTexture(bgTxt);
    background.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    background.setOrigin(bgTxt.getSize().x / 2.f, bgTxt.getSize().y / 2.f);

    Slash slash(window);

    int incr = 0;

    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        if (scene == 0) {
            sceneMenu(window,background,slash);
        }
        else {
            sceneGameplay(frameCount,incr, window,fruits,bombs,background,slash,textures);
        }
        
    }

    return 0;
}




