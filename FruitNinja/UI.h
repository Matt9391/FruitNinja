#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Slash.h"

#pragma once
class UI
{
public:
	//intializer
	static void init(sf::RenderWindow& window, sf::Texture& lifeTxt, sf::Texture& alertTxt, sf::SoundBuffer& musicBuff, sf::Texture& btnTxt);
	
	static void incrementScore();
	
	static void resetScore();
	
	static void resetAll();
	
	static bool decrementLives();	
	
	static void showGameOver(sf::RenderWindow& window);
	
	static void audioButtonHandler(sf::RenderWindow& window, Slash& slash);
	
	static void playSong();
	
	static void display(sf::RenderWindow& window);
	
	static bool gameOver;


private:
	//current score
	static int score;
	static int maxStreak;
	//total score
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

	static sf::Sound song;

	static bool songEnable;

	static sf::Text btnText;
	static sf::RectangleShape button;
	static sf::Sprite buttonGfx;
	//debounce to make the button clickable without going insane of timing ahah
	static int debounce;
};

