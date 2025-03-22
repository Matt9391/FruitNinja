#include "SFML/Graphics.hpp"

#pragma once
class UI
{
public:
	static void init(sf::RenderWindow& window, sf::Texture& lifeTxt);
	static void incrementScore();
	static void resetScore();
	static void resetAll();
	static bool decrementLives();

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

	static sf::Sprite lifeGfx;
};

