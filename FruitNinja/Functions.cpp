#include "Functions.h"
#include "Random.h"
#include "Menu.h"
#include "UI.h"

#include <iostream>
#include <cmath>

double degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0); 
}
double radiansToDegrees(double radians) {
    return radians * (180.0 / M_PI);
}

int constrain(int v, int min, int max) {
    if (v < min) {
        return min;
    }
    if (v > max) {
        return max;
    }
    return v;
}

float constrain(float v, float min, float max) {
    if (v < min) {
        return min;
    }
    if (v > max) {
        return max;
    }
    return v;
}

sf::Vector2f normalize(sf::Vector2f& v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    if (len != 0) {
        return v / len;
    }
    else {
        return sf::Vector2f(0.f, 0.f);
    }
}

float distance(const sf::Vector2f& v1,const sf::Vector2f& v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool checkCircleCollision(sf::CircleShape& a, sf::CircleShape& b) {
    float dist = distance(a.getPosition(), b.getPosition());
    float radii = a.getRadius() + b.getRadius();
    return dist < radii;
}


void spawnHalf(sf::Vector2f pos, float rad, float angle, std::vector<sf::Texture*> hFruitsTextures) {
    halfFruits.push_back(HalfFruit(pos, 3, rad*0.8, angle - M_PI /2 , 20, *hFruitsTextures[0], radiansToDegrees(angle)));
    halfFruits.push_back(HalfFruit(pos, 3, rad*0.8, angle + M_PI /2, 20, *hFruitsTextures[1], radiansToDegrees(angle)+360));
}

Fruit generateNewFruit(sf::RenderWindow& window, std::vector<sf::Texture>& txts) {
    float radius = window.getSize().y / 13.f;  // Raggio del frutto

    sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), window.getSize().y + radius);
    //std::cout << spawnPos.x;
    //spawnPos = sf::Vector2f(window.getSize().x / 2 - 10, window.getSize().y / 2 + 1);
    int minSpeed = (int)window.getSize().y / 32;
    int maxSpeed = (int)window.getSize().y / 28;

    sf::Vector2f sp(10, Random::randomInt(minSpeed, maxSpeed));

    sf::Vector2f targetPos((float)window.getSize().x / 2, (float)window.getSize().y / 2);

    int nTxt = Random::randomInt(0, 2) * 3;
    std::vector<sf::Texture*> hFruitsTextures = { &txts[nTxt + 1], &txts[nTxt + 2] };

    return Fruit(spawnPos, sp, radius, targetPos, txts[nTxt], hFruitsTextures);
}

Bomb generateNewBomb(sf::RenderWindow& window, std::vector<sf::Texture>& txts) {
    float radius = window.getSize().y / 14.f;  // Raggio del frutto

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



void sceneMenu(sf::RenderWindow& window, sf::Sprite& background, Slash& slash) {
    slash.update(window);
    Menu::update(window, slash);
    window.clear();
    window.draw(background);
    Menu::display(window);
    slash.display(window);
    window.display();
}

void sceneGameplay(int& frameCount, int& incr, sf::RenderWindow& window, std::vector<Fruit>& fruits, std::vector<Bomb>& bombs, sf::Sprite& background, Slash& slash, std::vector<sf::Texture>& textures) {
    bool sceneChanging = false;
    frameCount++;
    if ((frameCount % (40 - incr)) == 0) {
        fruits.push_back(generateNewFruit(window, textures));
        //std::cout << "Aggiunto: " << fruits.size() << std::endl;
    }
    if ((frameCount % (180 - incr)) == 0) {
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
                if (!UI::decrementLives()) {
                    sceneChanging = true;
                }
            }
            fruits.erase(fruits.begin() + i);  // Rimuovi l'elemento
            //std::cout <<"Tolto: "<<fruits.size()<<std::endl;
        }
    }



    for (Fruit& fruit : fruits) {
        fruit.update(window, slash.getHead());
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
                sceneChanging = true;
            }
            bombs.erase(bombs.begin() + i);  // Rimuovi l'elemento
            //std::cout <<"Tolto: "<<fruits.size()<<std::endl;
        }
    }

    for (Bomb& bomb : bombs) {
        bomb.update(window, slash.getHead());
    }

    window.clear();

    window.draw(background);

    for (Fruit& fruit : fruits) {
        fruit.display(window);
    }

    for (HalfFruit& hfruit : halfFruits) {
        hfruit.display(window);
    }

    for (Bomb& bomb : bombs) {
        bomb.display(window);
    }


    slash.display(window);

    UI::display(window);
    window.display();

    if (frameCount % 360 == 0) {
        incr++;
        incr = constrain(incr, 0,20);
    }

    if (sceneChanging) {
        incr = 0;
        changeScene(0);
    }
}

void changeScene(int nextScene) {
    fruits.clear();
    bombs.clear();
    halfFruits.clear();
    UI::resetAll();
    scene = nextScene;
}