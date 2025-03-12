#include "SFML/Graphics.hpp"
#include <vector>
#pragma once
class Slash
{
public:
	Slash();
	void display(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	std::vector<sf::CircleShape> getCircles();
private:

	bool checkSlashing();
	void moveSlash();
	void addCircle(sf::Vector2f& mousePos, sf::Vector2f* spawnPos);

	bool slashing;
	sf::VertexArray slash;
	std::vector<sf::CircleShape> circles;
};

