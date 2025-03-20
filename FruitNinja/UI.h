#include "SFML/Graphics.hpp"

#pragma once
class UI
{
public:
	static void init(sf::RenderWindow& window);
	static void incrementScore();
	static void decrementLives();

	static void display(sf::RenderWindow& window);
private:
	static int score;
	static int maxScore;
	static int lives;

	static sf::Font font;
	static sf::Text scoreTxt;
	static sf::Text maxScoreTxt;
	static sf::Text livesTxt;

	static bool initalized;
};

