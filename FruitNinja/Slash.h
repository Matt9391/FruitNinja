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

	bool slashing;
	sf::VertexArray slash;
	std::vector<sf::CircleShape> circles;
};

