#include "Menu.h"
#include "Functions.h"

#include <iostream>

sf::Font Menu::font;
sf::Text Menu::title;
sf::Text Menu::buttonStr;
sf::RectangleShape Menu::button;
bool Menu::initalized = false;

void Menu::init(sf::RenderWindow& window) {
	if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
		std::cerr << "Errore nel caricamento del font!" << std::endl;
		return;
	}

	title.setFont(font);
	buttonStr.setFont(font);

	title.setCharacterSize(45);
	buttonStr.setCharacterSize(45);

	title.setFillColor(sf::Color::White);
	buttonStr.setFillColor(sf::Color::White);

	title.setString("Fruit Ninja\n  by Matt");
	buttonStr.setString("Slash to start");
	
	sf::FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	
	textRect = buttonStr.getLocalBounds();
	buttonStr.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	sf::Vector2f pos(window.getSize().x / 2.f, window.getSize().y / 2.f);
	title.setPosition(pos + sf::Vector2f(0,-50.f));
	buttonStr.setPosition(pos + sf::Vector2f(0,150.f));

	button.setPosition(pos + sf::Vector2f(0, 150.f));
	button.setSize(sf::Vector2f(300, 80));
	button.setOrigin(button.getSize().x / 2.f, button.getSize().y / 2.f);
	button.setFillColor(sf::Color::Black);

	initalized = true;
}
void Menu::update(sf::RenderWindow& window, Slash& slash) {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui" << std::endl;
		throw std::exception("non hai inizializzato la ui");
		return;
	}
	
	if (!slash.getSlashing()) {
		return;
	}

	sf::Vector2f slashPos = slash.getHead().getPosition();

	if (slashPos.x > button.getPosition().x - button.getSize().x / 2.f &&
		slashPos.x < button.getPosition().x + button.getSize().x / 2.f &&
		slashPos.y > button.getPosition().y - button.getSize().y / 2.f &&
		slashPos.y < button.getPosition().y + button.getSize().y / 2.f
		) {
		changeScene(1);
	}
}

void Menu::display(sf::RenderWindow& window) {
	if (!initalized) {
		std::cout << "non hai inizializzato la ui" << std::endl;
		throw std::exception("non hai inizializzato la ui");
		return;
	}

	window.draw(title);
	window.draw(button);
	window.draw(buttonStr);
}