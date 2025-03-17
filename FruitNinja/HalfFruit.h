#include "SFML/Graphics.hpp"
#pragma once

class HalfFruit
{
public:

	HalfFruit(sf::Vector2f pos, float speed, float radius, float angle, int lifespan);

	void update();
	void display(sf::RenderWindow& window);
	void setDir(float angle);
	void setVelocity();
	void addGravity();

	bool toRemove;
private:

	sf::Vector2f pos;
	sf::CircleShape shape;
	float speed;
	float radius;
	float gravity;

	sf::Vector2f velocity;
	sf::Vector2f dir;

	int lifespan;
};

