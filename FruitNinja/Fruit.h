#include <SFML/Graphics.hpp>

#pragma once
class Fruit
{

public:

	Fruit(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos);

	void update(sf::RenderWindow& w, sf::CircleShape circle);
	void display(sf::RenderWindow& window);
	void setDir(sf::Vector2f targetPos);
	void addGravity();
	void setVelocity();
	
	sf::Vector2f pos;
	bool toRemove;
	bool slashed;
private:
	void outOfBound(sf::RenderWindow& window);
	void checkSlashCollision(sf::RenderWindow& w,sf::CircleShape& circle);
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f speed;
	float radius;

	sf::Vector2f dir;
	float gravity;
};

