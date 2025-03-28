#include "Menu.h"
#include "Functions.h"

#include <iostream>

sf::Font Menu::font;
sf::Text Menu::title;
sf::Text Menu::btnText;
sf::RectangleShape Menu::button;
sf::Sprite Menu::buttonGfx;
bool Menu::initalized = false;

void Menu::init(sf::RenderWindow& window, sf::Texture& btnTxt) {
	if (!font.loadFromFile("./Fonts/LazyFox Pixel Font 2.ttf")) {
		std::cerr << "Errore nel caricamento del font!" << std::endl;
		return;
	}

	title.setFont(font);
	btnText.setFont(font);

	title.setCharacterSize(45);
	btnText.setCharacterSize(35);

	title.setFillColor(sf::Color::White);
	btnText.setFillColor(sf::Color(80,50,50));

	title.setString("Fruit Ninja\n  by Matt");
	btnText.setString("Slash to start");
	
	sf::FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	sf::Vector2f pos(window.getSize().x / 2.f, window.getSize().y / 2.f);
	title.setPosition(pos + sf::Vector2f(0,-150.f));

	textRect = btnText.getLocalBounds();
	btnText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	btnText.setPosition(pos + sf::Vector2f(0, 150.f));

	button.setPosition(pos + sf::Vector2f(0, 150.f));
	button.setSize(sf::Vector2f(310, 80));
	button.setOrigin(button.getSize().x / 2.f, button.getSize().y / 2.f);
	button.setFillColor(sf::Color::Black);

	buttonGfx.setTexture(btnTxt);
	buttonGfx.setScale(5.5, 2.5);
	buttonGfx.setOrigin(btnTxt.getSize().x / 2.f, btnTxt.getSize().y / 2.f);
	buttonGfx.setPosition(pos + sf::Vector2f(0, 150.f));

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
	window.draw(buttonGfx);
	window.draw(btnText);
	//window.draw(button);
}