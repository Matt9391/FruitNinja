#include "SFML/Graphics.hpp"
#include <vector>
#pragma once
class Slash
{
public:
	Slash();
	void display(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
private:

	bool checkSlashing();
	
	bool slashing;
	sf::VertexArray slash;
	std::vector<sf::CircleShape> circles;
};

