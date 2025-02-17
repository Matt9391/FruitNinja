#include <iostream>
#include <SFML/Graphics.hpp>
#include "Fruit.h"
#include "Random.h"

Fruit generateNewFruit(sf::RenderWindow& window);

int main()
{
    Random::Init();
    int frameCount = 0;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Fruit Ninja");
    window.setFramerateLimit(60);
    //float radius = 25.f;  // Raggio del frutto
    
    //sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), 500);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    //sf::Vector2f sp(10, 25);
    //Fruit fruit(spawnPos, sp, radius, window);

    std::vector<Fruit> fruits;
    //fruits.push_back(fruit);

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
            std::cout << "Aggiunto: " << fruits.size() << std::endl;
        }

        for (int i = fruits.size() - 1; i >= 0; --i) {
            Fruit& f = fruits[i];  // Usa un riferimento per evitare la copia
            if (f.toRemove) {
                fruits.erase(fruits.begin() + i);  // Rimuovi l'elemento
                std::cout <<"Tolto: "<<fruits.size()<<std::endl;

            }
        }



        for (Fruit& fruit : fruits) {
            fruit.update();
        }


        window.clear();

        for (Fruit& fruit : fruits) {
            fruit.display(window);
        }

        window.display();

        
    }

    return 0;
}

Fruit generateNewFruit(sf::RenderWindow &window) {
    float radius = 35.f;  // Raggio del frutto

    sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), 650);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    sf::Vector2f sp(10, Random::randomInt(18,23));

    return Fruit(spawnPos, sp, radius, window);
}
