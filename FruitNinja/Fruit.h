#include <SFML/Graphics.hpp>

#pragma once
class Fruit
{

public:

	Fruit(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::RenderWindow& window);

	void update(const std::vector<sf::CircleShape>& circles);
	void display(sf::RenderWindow& window);
	void setDir(sf::Vector2f targetPos);
	void addGravity();
	void setVelocity();
	
	sf::Vector2f pos;
	bool toRemove;
private:
	void outOfBound();
	void checkSlashCollision(const std::vector<sf::CircleShape>& circles);
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f speed;
	float radius;

	sf::Vector2f dir;
	float gravity;
};

