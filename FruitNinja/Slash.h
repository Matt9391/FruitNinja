#include "SFML/Graphics.hpp"
#include <vector>
#pragma once
class Slash
{
public:
	Slash(sf::RenderWindow& window);
	void display(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	sf::CircleShape getHead();

	bool getSlashing();
private:

	bool checkSlashing();
	void moveSlash();
	void addCircle(sf::Vector2f& mousePos, sf::Vector2f* spawnPos);

	bool slashing;
	int maxTails;
	float radius;
	sf::VertexArray slash;
	std::vector<sf::CircleShape> circles;
};

