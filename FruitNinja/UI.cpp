#include <iostream>

#include "UI.h"
#include "Functions.h"

int UI::score = 0;
int UI::maxScore = 0;
int UI::maxStreak = 0;
int UI::lives = 3;
int UI::alertTime = 120;

bool UI::gameOver = false;
bool UI::initalized = false;

sf::Font UI::font;
sf::Text UI::scoreText;
sf::Text UI::maxStreakText;
sf::Text UI::livesText;
sf::Text UI::alertText;

sf::Sprite UI::lifeGfx;
sf::Sprite UI::alertGfx;

void UI::init(sf::RenderWindow& window, sf::Texture& lifeTxt, sf::Texture& alertTxt) {
	if (!font.loadFromFile("./Fonts/LazyFox Pixel Font 2.ttf")) {
		std::cerr << "Errore nel caricamento del font!" << std::endl;
		return;
	}

	lifeGfx.setTexture(lifeTxt);
	lifeGfx.setOrigin(lifeTxt.getSize().x / 2.f, lifeTxt.getSize().y / 2.f);
	lifeGfx.setScale(5, 5);

	alertGfx.setTexture(alertTxt);
	alertGfx.setOrigin(alertTxt.getSize().x / 2.f, alertTxt.getSize().y / 2.f);
	alertGfx.setScale(7, 3.5);
	alertGfx.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

	scoreText.setFont(font); 
	maxStreakText.setFont(font);
	livesText.setFont(font); 
	alertText.setFont(font); 

	scoreText.setCharacterSize(65);
	maxStreakText.setCharacterSize(25);
	livesText.setCharacterSize(25);
	alertText.setCharacterSize(25);

	scoreText.setFillColor(sf::Color::White);
	maxStreakText.setFillColor(sf::Color::White);
	livesText.setFillColor(sf::Color::White);
	alertText.setFillColor(sf::Color::White);
	//alertText.setFillColor(sf::Color(50,50,50));

	scoreText.setString(std::to_string(score));
	maxStreakText.setString(std::to_string(maxStreak));
	livesText.setString(std::to_string(lives));
	alertText.setString("Hai perso looser");

	scoreText.setPosition(sf::Vector2f(window.getSize().x / 2, 50));
	maxStreakText.setPosition(sf::Vector2f(window.getSize().x / 20, 50));
	livesText.setPosition(sf::Vector2f(window.getSize().x / 20, 100));
	alertText.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
	
	sf::FloatRect textRect = alertText.getLocalBounds();
	alertText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	gameOver = false;
	initalized = true;
}

void UI::incrementScore() {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui"<<std::endl;
		throw std::exception("non hai inizializzato la ui");
		return;
	}

	score++;
	maxScore++;
	if (score >= maxStreak) {
		maxStreak = score;
	}
}
void UI::resetScore() {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui"<<std::endl;
		throw std::exception("non hai inizializzato la ui");
		return;
	}

	score = 0;
}

void UI::resetAll() {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui" << std::endl;
		throw std::exception("non hai inizializzato la ui");
		return;
	}

	score = 0;
	maxStreak = 0;
	lives = 3;
	gameOver = false;
	alertTime = 120;
}

bool UI::decrementLives() {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui" << std::endl;
		throw std::exception("non hai inizializzato la ui");
		return false;
	}
	
	resetScore();

	if (lives > 1) {
		lives--;
		return true;
	}

	std::cout << "hai perso";
	return false;
}

void UI::showGameOver(sf::RenderWindow& window) {
	if (!gameOver) {
		return;
	}
	
	if (alertTime < 0) {
		return;
	}

	alertTime--;

	window.draw(alertGfx);
	window.draw(alertText);

}

void UI::display(sf::RenderWindow& window) {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui" << std::endl;
		throw std::exception("non hai inizializzato la ui");
		return;
	}

	// Aggiorna l'origine per centrare il testo
	sf::FloatRect textRect = scoreText.getLocalBounds();
	scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	// Assicurati di aver settato la posizione al centro della finestra
	scoreText.setPosition(sf::Vector2f(window.getSize().x / 2, 50));

	scoreText.setString(std::to_string(score));
	maxStreakText.setString("Top Streak: " + std::to_string(maxStreak));
	
	for (int i = 0; i < lives; i++) {
		lifeGfx.setPosition(window.getSize().x - 100 * i - 50, 50);
		window.draw(lifeGfx);
	}
	//livesTxt.setString(str);

	window.draw(scoreText);
	window.draw(maxStreakText);
	//window.draw(livesTxt);
}