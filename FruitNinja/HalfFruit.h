#include "SFML/Graphics.hpp"
#pragma once

class HalfFruit
{
public:

	HalfFruit(sf::Vector2f pos, float speed, float radius, float angle, int lifespan, sf::Texture& txt, float gfxAngle);

	void update();
	
	void setDir(float angle);
	void setVelocity();
	
	void addGravity();
	
	void display(sf::RenderWindow& window);

	bool toRemove;
private:

	sf::Vector2f pos;
	sf::CircleShape shape;

	float speed;
	float radius;
	float gravity;

	sf::Vector2f velocity;
	sf::Vector2f dir;

	//num of frames that it last
	int lifespan;

	sf::Sprite gfx;
};

