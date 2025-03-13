#include "Functions.h"
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


void spawnHalf(sf::Vector2f pos, float rad, float angle) {
    halfFruits.push_back(HalfFruit(pos, 5, rad*0.8, angle + 0.15f, 20));
    halfFruits.push_back(HalfFruit(pos, 5, rad*0.8, angle + 0.15f + M_PI, 20));
}