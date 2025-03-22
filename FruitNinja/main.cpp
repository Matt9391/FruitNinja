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

Fruit generateNewFruit(sf::RenderWindow& window, std::vector<sf::Texture>& txs);
Bomb generateNewBomb(sf::RenderWindow& window, std::vector<sf::Texture>& txts);

std::vector<HalfFruit> halfFruits;

int main()
{    
    Random::Init();
    int frameCount = 0;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fruit Ninja");
    window.setFramerateLimit(60);
    //float radius = 25.f;  // Raggio del frutto
    
    UI::init(window);
    //sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), 500);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    //sf::Vector2f sp(10, 25);
    //Fruit fruit(spawnPos, sp, radius, window);

    std::vector<Fruit> fruits;
    std::vector<Bomb> bombs;
    //fruits.push_back(fruit);

    sf::Texture txt;
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
        "./Sprites/plum.png"
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

    Slash slash(window);

    while (window.isOpen())
    {
        frameCount++;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        if (frameCount % 40 == 0) {
            fruits.push_back(generateNewFruit(window, textures));
            //std::cout << "Aggiunto: " << fruits.size() << std::endl;
        }
        if (frameCount % 180 == 0) {
            bombs.push_back(generateNewBomb(window, textures));
            //std::cout << "Aggiunto: " << fruits.size() << std::endl;
        }
        slash.update(window);

        for (int i = fruits.size() - 1; i >= 0; --i) {
            Fruit& f = fruits[i];  // Usa un riferimento per evitare la copia
            if (f.toRemove) {
                if (f.slashed) {
                    UI::incrementScore();
                }
                else {
                    UI::decrementLives();
                }
                fruits.erase(fruits.begin() + i);  // Rimuovi l'elemento
                //std::cout <<"Tolto: "<<fruits.size()<<std::endl;
            }
        }



        for (Fruit& fruit : fruits) {
            fruit.update(window,slash.getHead());
        }

        for (int i = halfFruits.size() - 1; i >= 0; --i) {
            HalfFruit& hfruit = halfFruits[i];
            hfruit.update();
            if (hfruit.toRemove) {
                halfFruits.erase(halfFruits.begin() + i);
            }
        }

        for (int i = bombs.size() - 1; i >= 0; --i) {
            Bomb& b = bombs[i];  // Usa un riferimento per evitare la copia
            if (b.toRemove) {
                if (b.slashed) {
                    UI::resetScore();
                }
                bombs.erase(bombs.begin() + i);  // Rimuovi l'elemento
                //std::cout <<"Tolto: "<<fruits.size()<<std::endl;
            }
        }

        for (Bomb& bomb : bombs) {
            bomb.update(window, slash.getHead());
        }

        window.clear();

        for (Fruit& fruit : fruits) {
            fruit.display(window);
        }

        for (HalfFruit& hfruit : halfFruits) {
            hfruit.display(window);
        }

        for (Bomb& bomb: bombs) {
            bomb.display(window);
        }


        slash.display(window);

        UI::display(window);
        window.display();

        
    }

    return 0;
}


Fruit generateNewFruit(sf::RenderWindow &window, std::vector<sf::Texture>& txts) {
    float radius = window.getSize().y / 13.f;  // Raggio del frutto

    sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), window.getSize().y + radius);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    int minSpeed = (int)window.getSize().y / 32;
    int maxSpeed = (int)window.getSize().y / 28;

    sf::Vector2f sp(10, Random::randomInt(minSpeed, maxSpeed));

    sf::Vector2f targetPos((float)window.getSize().x / 2, (float)window.getSize().y / 2);

    int nTxt = Random::randomInt(0, 2) * 3;
    std::vector<sf::Texture*> hFruitsTextures = { &txts[nTxt+1], &txts[nTxt + 2] };

    return Fruit(spawnPos, sp, radius, targetPos, txts[nTxt], hFruitsTextures);
}

Bomb generateNewBomb(sf::RenderWindow &window, std::vector<sf::Texture>& txts) {
    float radius = window.getSize().y / 13.f;  // Raggio del frutto

    sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), window.getSize().y + radius);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    int minSpeed = (int)window.getSize().y / 32;
    int maxSpeed = (int)window.getSize().y / 28;

    sf::Vector2f sp(10, Random::randomInt(minSpeed, maxSpeed));

    sf::Vector2f targetPos((float)window.getSize().x / 2, (float)window.getSize().y / 2);

    int nTxt = 9;

    return Bomb(spawnPos, sp, radius, targetPos, txts[nTxt]);
}
