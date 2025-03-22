#include "SFML/Graphics.hpp"
#include "HalfFruit.h"
#include "Bomb.h"
#include "Fruit.h"
#include "Slash.h"
#include <cmath>
#pragma once

#define M_PI 3.14159265358979323846

extern std::vector<HalfFruit> halfFruits;
extern std::vector<Fruit> fruits;
extern std::vector<Bomb> bombs;
extern int scene;

double degreesToRadians(double degrees);
double radiansToDegrees(double radians);

int constrain(int v, int min, int max);
float constrain(float v, float min, float max);

sf::Vector2f normalize(sf::Vector2f& v);

float distance(const sf::Vector2f& v1,const sf::Vector2f& v2);

bool checkCircleCollision(sf::CircleShape& a, sf::CircleShape& b);

void spawnHalf(sf::Vector2f pos, float rad, float angle, std::vector<sf::Texture*> hFruitsTextures);

Fruit generateNewFruit(sf::RenderWindow& window, std::vector<sf::Texture>& txs);
Bomb generateNewBomb(sf::RenderWindow& window, std::vector<sf::Texture>& txts);

void sceneMenu(sf::RenderWindow& window, sf::Sprite& background, Slash& slash);
void sceneGameplay(int& frameCount, int& incr, sf::RenderWindow& window, std::vector<Fruit>& fruits, std::vector<Bomb>& bombs, sf::Sprite& background, Slash& slash, std::vector<sf::Texture>& textures);
void changeScene(int nextScene);