#include "SFML/Graphics.hpp"
#include "Slash.h"

#pragma once
class Menu
{
public:
	static void init(sf::RenderWindow& window, sf::Texture& btnTxt);
	static void update(sf::RenderWindow& window, Slash& slash);
	static void display(sf::RenderWindow& window);
private:
	
	static sf::Font font;
	static sf::Text title;
	static sf::RectangleShape button;
	static sf::Sprite buttonGfx;
	static bool initalized;
};

