#include <iostream>
#include <SFML/Graphics.hpp>
#include "Fruit.h"
#include <random>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fruit Ninja");
    
    float radius = 50.f;  // Raggio del frutto
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(radius, window.getSize().x - radius);

    sf::Vector2f spawnPos(dist(gen), 100);
    std::cout << spawnPos.x;
    Fruit fruit(spawnPos, 15, radius);
    
 

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

        window.clear();
        fruit.display(window);
        window.display();
    }

    return 0;
}