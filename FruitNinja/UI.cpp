#include <iostream>

#include "UI.h"
#include "Functions.h"

int UI::score = 0;
int UI::maxScore = 0;
int UI::lives = 3;
bool UI::initalized = false;
sf::Font UI::font;
sf::Text UI::scoreTxt;
sf::Text UI::maxScoreTxt;
sf::Text UI::livesTxt;
sf::Sprite UI::lifeGfx;

void UI::init(sf::RenderWindow& window, sf::Texture& lifeTxt) {
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
		std::cerr << "Errore nel caricamento del font!" << std::endl;
		return;
	}

	lifeGfx.setTexture(lifeTxt);
	lifeGfx.setOrigin(lifeTxt.getSize().x / 2.f, lifeTxt.getSize().y / 2.f);
	lifeGfx.setScale(5, 5);

	scoreTxt.setFont(font); 
	maxScoreTxt.setFont(font);
	livesTxt.setFont(font); 

	scoreTxt.setCharacterSize(45);
	maxScoreTxt.setCharacterSize(25);
	livesTxt.setCharacterSize(25);

	scoreTxt.setFillColor(sf::Color::White);
	maxScoreTxt.setFillColor(sf::Color::White);
	livesTxt.setFillColor(sf::Color::White);

	scoreTxt.setString(std::to_string(score));
	maxScoreTxt.setString(std::to_string(maxScore));
	livesTxt.setString(std::to_string(lives));

	scoreTxt.setPosition(sf::Vector2f(window.getSize().x / 2, 50));
	maxScoreTxt.setPosition(sf::Vector2f(window.getSize().x / 20, 50));
	livesTxt.setPosition(sf::Vector2f(window.getSize().x / 20, 100));

	initalized = true;
}


void UI::incrementScore() {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui"<<std::endl;
		throw std::exception("non hai inizializzato la ui");
		return;
	}

	score++;
	if (score >= maxScore) {
		maxScore = score;
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
	maxScore = 0;
	lives = 3;
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

void UI::display(sf::RenderWindow& window) {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui" << std::endl;
		throw std::exception("non hai inizializzato la ui");
		return;
	}

	// Aggiorna l'origine per centrare il testo
	sf::FloatRect textRect = scoreTxt.getLocalBounds();
	scoreTxt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	// Assicurati di aver settato la posizione al centro della finestra
	scoreTxt.setPosition(sf::Vector2f(window.getSize().x / 2, 50));

	scoreTxt.setString(std::to_string(score));
	maxScoreTxt.setString("maxScore: " + std::to_string(maxScore));
	
	for (int i = 0; i < lives; i++) {
		lifeGfx.setPosition(window.getSize().x - 100 * i - 50, 50);
		window.draw(lifeGfx);
	}
	//livesTxt.setString(str);

	window.draw(scoreTxt);
	window.draw(maxScoreTxt);
	//window.draw(livesTxt);
}