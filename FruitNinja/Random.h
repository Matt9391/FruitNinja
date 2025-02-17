#include <random>

#pragma once
class Random
{
public:
	static void Init();
	static float randomFloat(float min, float max);
	static int randomInt(int min, int max);


private:
	static std::random_device rd;
	static std::mt19937 gen;
};

