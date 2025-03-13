#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Fruit.h"
#include "Functions.h"
#include "Random.h"
#include "Slash.h"
#include "HalfFruit.h"

Fruit generateNewFruit(sf::RenderWindow& window);

std::vector<HalfFruit> halfFruits;

int main()
{    
    Random::Init();
    int frameCount = 0;
    int score = 0;

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Errore nel caricamento del font!" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font); // Imposta il font
    text.setCharacterSize(45); // Dimensione del testo
    text.setFillColor(sf::Color::White); // Colore del testo
    text.setPosition(600, 50); // Posizione del testo


    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fruit Ninja");
    window.setFramerateLimit(60);
    //float radius = 25.f;  // Raggio del frutto
    
    //sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), 500);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    //sf::Vector2f sp(10, 25);
    //Fruit fruit(spawnPos, sp, radius, window);

    std::vector<Fruit> fruits;
    //fruits.push_back(fruit);

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

        if (frameCount % 60 == 0) {
            fruits.push_back(generateNewFruit(window));
            //std::cout << "Aggiunto: " << fruits.size() << std::endl;
        }

        slash.update(window);

        for (int i = fruits.size() - 1; i >= 0; --i) {
            Fruit& f = fruits[i];  // Usa un riferimento per evitare la copia
            if (f.toRemove) {
                if (f.slashed) {
                    score++;
                }
                else {
                    score = 0;
                }
                text.setString(std::to_string(score));
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

        window.clear();

        for (Fruit& fruit : fruits) {
            fruit.display(window);
        }

        for (HalfFruit& hfruit : halfFruits) {
            hfruit.display(window);
        }


        slash.display(window);
        window.draw(text);
        window.display();

        
    }

    return 0;
}

Fruit generateNewFruit(sf::RenderWindow &window) {
    float radius = window.getSize().y / 13;  // Raggio del frutto

    sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), window.getSize().y + radius);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    int minSpeed = window.getSize().y / 32;
    int maxSpeed = window.getSize().y / 28;

    sf::Vector2f sp(10, Random::randomInt(minSpeed, maxSpeed));

    sf::Vector2f targetPos((float)window.getSize().x / 2, (float)window.getSize().y / 2);
    return Fruit(spawnPos, sp, radius, targetPos);
}
