#include "SFML/Graphics.hpp"
#include <cmath>
#pragma once

#define M_PI 3.14159265358979323846

double degreesToRadians(double degrees);
double radiansToDegrees(double radians);

int constrain(int v, int min, int max);
float constrain(float v, float min, float max);

sf::Vector2f normalize(sf::Vector2f& v);
