#include "Functions.h"
#include "Random.h"
#include "Menu.h"
#include "UI.h"

#include <iostream>
#include <cmath>

//angle conversion
float degreesToRadians(float degrees) {
    return static_cast<float>(degrees * (M_PI / 180.0f)); 
}
float radiansToDegrees(float radians) {
    return static_cast<float>(radians * (180.0f / M_PI));
}

//constrain the given value in the bounds
int constrain(int v, int min, int max) {
    if (v < min) {
        return min;
    }
    if (v > max) {
        return max;
    }
    return v;
}

//constrain the given value in the bounds
float constrain(float v, float min, float max) {
    if (v < min) {
        return min;
    }
    if (v > max) {
        return max;
    }
    return v;
}

//function that normalize a vector
sf::Vector2f normalize(sf::Vector2f& v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    if (len != 0) {
        return v / len;
    }
    else {
        return sf::Vector2f(0.f, 0.f);
    }
}

//function that caluclate the distance between 2 points
float distance(const sf::Vector2f& v1,const sf::Vector2f& v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return std::sqrt(dx * dx + dy * dy);
}

//function that check circle cillisoin between 2 circles
bool checkCircleCollision(sf::CircleShape& a, sf::CircleShape& b) {
    float dist = distance(a.getPosition(), b.getPosition());
    float radii = a.getRadius() + b.getRadius();
    return dist < radii;
}

//method that spawn 2 halfFruits
void spawnHalf(sf::Vector2f pos, float rad, float angle, std::vector<sf::Texture*> hFruitsTextures) {
    //just set the angle of the fruit and the graphics related to it
    halfFruits.push_back(HalfFruit(pos, 3.f, rad*0.8f, angle - M_PI / 2.f , 20, *hFruitsTextures[0], radiansToDegrees(angle)));
    halfFruits.push_back(HalfFruit(pos, 3.f, rad*0.8f, angle + M_PI / 2.f, 20, *hFruitsTextures[1], radiansToDegrees(angle)+360));
}

//function that generate a new entity
Fruit generateNewFruit(sf::RenderWindow& window, std::vector<sf::Texture>& txts) {
    float radius = window.getSize().y / 13.f;  // radius of the fruit (scaled with the screen)

    sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), window.getSize().y + radius);
    
    int minSpeed = (int)window.getSize().y / 32;
    int maxSpeed = (int)window.getSize().y / 28;
    
    //sp = speed
    sf::Vector2f sp(10, Random::randomInt(minSpeed, maxSpeed));

    //its a variation of position spawn
    float sens = window.getSize().x / 10.f;

    sf::Vector2f targetPos((float)window.getSize().x / 2 + Random::randomFloat(-sens, sens), (float)window.getSize().y / 2);

    //take one of 3 full sprite index
    int nTxt = Random::randomInt(0, 2) * 3;
    std::vector<sf::Texture*> hFruitsTextures = { &txts[nTxt + 1], &txts[nTxt + 2] };

    return Fruit(spawnPos, sp, radius, targetPos, txts[nTxt], hFruitsTextures);
}

Bomb generateNewBomb(sf::RenderWindow& window, std::vector<sf::Texture>& txts) {
    float radius = window.getSize().y / 14.f;  // radius of the fruit (scaled with the screen)

    sf::Vector2f spawnPos(Random::randomFloat(radius, window.getSize().x - radius), window.getSize().y + radius);

    int minSpeed = (int)window.getSize().y / 32;
    int maxSpeed = (int)window.getSize().y / 28;

    //sp = speed
    sf::Vector2f sp(10, Random::randomInt(minSpeed, maxSpeed));

    //its a variation of position spawn
    float sens = window.getSize().x / 10.f;
    sf::Vector2f targetPos((float)window.getSize().x / 2.f + Random::randomFloat(-sens, sens), (float)window.getSize().y / 2.f);

    //take one of 9th index of the vector
    int nTxt = 9;

    return Bomb(spawnPos, sp, radius, targetPos, txts[nTxt]);
}


void sceneMenu(sf::RenderWindow& window, sf::Sprite& background, Slash& slash) {
    UI::playSong();
    
    slash.update(window);
    Menu::update(window, slash);

    window.clear();
    window.draw(background);
    
    UI::showGameOver(window);
    UI::audioButtonHandler(window,slash);

    Menu::display(window);
    slash.display(window);
    
    window.display();
}

void sceneGameplay(int& frameCount, int& incr, sf::RenderWindow& window, std::vector<Fruit>& fruits, std::vector<Bomb>& bombs, sf::Sprite& background, Slash& slash, std::vector<sf::Texture>& textures) {
    UI::playSong();
    bool sceneChanging = false;

    //increase framecount each frame
    frameCount++;

    if ((frameCount % (40 - incr)) == 0) {
        fruits.push_back(generateNewFruit(window, textures));
    }
    if ((frameCount % (180 - incr)) == 0) {
        bombs.push_back(generateNewBomb(window, textures));
    }

    slash.update(window);

    for (int i = fruits.size() - 1; i >= 0; --i) {
        Fruit& f = fruits[i];
        if (f.toRemove) {
            if (f.slashed) {
                UI::incrementScore();
            }
            else {
                if (!UI::decrementLives()) {
                    sceneChanging = true;
                }
            }
            fruits.erase(fruits.begin() + i); 
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
        Bomb& b = bombs[i];
        if (b.toRemove) {
            if (b.slashed) {
                UI::resetScore();
                //set the need to change the scene a true
                sceneChanging = true;
            }
            bombs.erase(bombs.begin() + i);  
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
        UI::gameOver = true;
        changeScene(0);
    }
}

void changeScene(int nextScene) {
    fruits.clear();
    bombs.clear();
    halfFruits.clear();
    scene = nextScene;
    if (nextScene != 0) {
        UI::resetAll();
    }
}

bool checkAABB(sf::Vector2f& point, sf::RectangleShape& rect) {
    if (point.x > rect.getPosition().x - rect.getSize().x / 2.f &&
        point.x < rect.getPosition().x + rect.getSize().x / 2.f &&
        point.y > rect.getPosition().y - rect.getSize().y / 2.f &&
        point.y < rect.getPosition().y + rect.getSize().y / 2.f
        ) {
        return true;
    }
    return false;
}