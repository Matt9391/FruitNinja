#include "SFML/Graphics.hpp"

#pragma once
class Entity
{
public:
	Entity(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt);

	void update(sf::RenderWindow& window,sf::CircleShape circle);
	void display(sf::RenderWindow& window);
	void setDir(sf::Vector2f targetPos);
	void addGravity();
	void setVelocity();

	sf::Vector2f pos;
	bool toRemove;
	bool slashed;
protected:
	void outOfBound(sf::RenderWindow& window);
	bool checkSlashCollision(sf::CircleShape& circle);
	void rotateSprite();

	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f speed;
	float radius;

	sf::Vector2f dir;
	float gravity;

	sf::Sprite gfx;
	sf::Texture txt;
	int angle;
	int angleInc;
};

