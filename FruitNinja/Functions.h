#include "SFML/Graphics.hpp"
#include "HalfFruit.h"
#include "Bomb.h"
#include "Fruit.h"
#include "Slash.h"
#include <cmath>
#pragma once

//PI ._. 
#define M_PI 3.14159265358979323846f

//vectors of game objects
extern std::vector<HalfFruit> halfFruits;
extern std::vector<Fruit> fruits;
extern std::vector<Bomb> bombs;
extern int scene;

//angle conversion
float degreesToRadians(float degrees);
float radiansToDegrees(float radians);

//constrain the given value in the bounds
int constrain(int v, int min, int max);
float constrain(float v, float min, float max);

//function that normalize a vector
sf::Vector2f normalize(sf::Vector2f& v);

//function that caluclate the distance between 2 points
float distance(const sf::Vector2f& v1,const sf::Vector2f& v2);

//function that check circle cillisoin between 2 circles
bool checkCircleCollision(sf::CircleShape& a, sf::CircleShape& b);

//method that spawn 2 halfFruits
void spawnHalf(sf::Vector2f pos, float rad, float angle, std::vector<sf::Texture*> hFruitsTextures);

//function that generate a new entity
Fruit generateNewFruit(sf::RenderWindow& window, std::vector<sf::Texture>& txs);
Bomb generateNewBomb(sf::RenderWindow& window, std::vector<sf::Texture>& txts);

//scene of menu
void sceneMenu(sf::RenderWindow& window, sf::Sprite& background, Slash& slash);
//scene of gameplay
void sceneGameplay(int& frameCount, int& incr, sf::RenderWindow& window, std::vector<Fruit>& fruits, std::vector<Bomb>& bombs, sf::Sprite& background, Slash& slash, std::vector<sf::Texture>& textures);
//method that change scene
void changeScene(int nextScene);

//its strightforward
bool checkAABB(sf::Vector2f& point, sf::RectangleShape& rect);