#include "Entity.h"

#pragma once
//Fruit that inheritance from Entity
class Fruit : public Entity
{

public:
	Fruit(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt, std::vector<sf::Texture*> hTxts);

	void update(sf::RenderWindow& window,sf::CircleShape circle);

private:
	//textures for halfFruits that generate once it gets sliced
	std::vector<sf::Texture*> hTxts;
};

