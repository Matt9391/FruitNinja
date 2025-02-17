#include "Functions.h"

double degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0); 
}
double radiansToDegrees(double radians) {
    return radians * (180.0 / M_PI);
}