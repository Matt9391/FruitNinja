#include "Functions.h"

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