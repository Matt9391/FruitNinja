#include <SFML/Graphics.hpp>

#pragma once
class Fruit
{

public:
	sf::Vector2f pos;

	Fruit(sf::Vector2f pos, float speed, float radius);

	void update();
	void display(sf::RenderWindow& window);

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	float speed;
	float radius;
};

