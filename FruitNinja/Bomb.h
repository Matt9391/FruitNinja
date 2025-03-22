#include "Entity.h"

#pragma once
class Bomb : public Entity
{
public:
	Bomb(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt);
	
	void update(sf::RenderWindow& window, sf::CircleShape circle);
	//void display(sf::RenderWindow& window);

};

