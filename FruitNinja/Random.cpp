#include "Random.h"

std::random_device Random::rd;
std::mt19937 Random::gen;

void Random::Init() {
	gen.seed(rd());
}

float Random::randomFloat(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}
int Random::randomInt(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}