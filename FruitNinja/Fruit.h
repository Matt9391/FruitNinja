#include "Entity.h"

#pragma once
class Fruit : public Entity
{

public:
	Fruit(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt, std::vector<sf::Texture*> hTxts);

	void update(sf::RenderWindow& window,sf::CircleShape circle);
	//void display(sf::RenderWindow& window);

private:
	std::vector<sf::Texture*> hTxts;
};

