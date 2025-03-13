#include "SFML/Graphics.hpp"
#include "HalfFruit.h"
#include <cmath>
#pragma once

#define M_PI 3.14159265358979323846

extern std::vector<HalfFruit> halfFruits;

double degreesToRadians(double degrees);
double radiansToDegrees(double radians);

int constrain(int v, int min, int max);
float constrain(float v, float min, float max);

sf::Vector2f normalize(sf::Vector2f& v);

float distance(const sf::Vector2f& v1,const sf::Vector2f& v2);

bool checkCircleCollision(sf::CircleShape& a, sf::CircleShape& b);

void spawnHalf(sf::Vector2f pos, float rad, float angle);