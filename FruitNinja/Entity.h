#include "SFML/Graphics.hpp"

#pragma once
class Entity
{
public:
	Entity(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt);

	void update(sf::RenderWindow& window,sf::CircleShape circle);

	//set the dir of the entity
	void setDir(sf::Vector2f targetPos);
	
	//set the velocity of the entity
	void setVelocity();
	
	void addGravity();

	void display(sf::RenderWindow& window);

	//position of the entity
	sf::Vector2f pos;

	bool toRemove;
	bool slashed;

protected:
	//check if it is out of bounds
	void outOfBound(sf::RenderWindow& window);
	//check if the slash collide with an entity
	bool checkSlashCollision(sf::CircleShape& circle);
	void rotateSprite();

	//hitbox of the entity
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

