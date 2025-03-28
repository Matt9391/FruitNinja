#include "SFML/Graphics.hpp"

#pragma once
class UI
{
public:
	static void init(sf::RenderWindow& window, sf::Texture& lifeTxt, sf::Texture& alertTxt);
	static void incrementScore();
	static void resetScore();
	static void resetAll();
	static bool decrementLives();

	static void display(sf::RenderWindow& window);
	static void showGameOver(sf::RenderWindow& window);
	
	static bool gameOver;

private:
	static int score;
	static int maxStreak;
	static int maxScore;
	static int lives;

	static sf::Font font;
	static sf::Text scoreText;
	static sf::Text maxStreakText;
	static sf::Text livesText;
	static sf::Text alertText;

	static bool initalized;

	static int alertTime;

	static sf::Sprite lifeGfx;
	static sf::Sprite alertGfx;
};

