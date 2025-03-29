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

	sf::Vector2f hfScreen(window.getSize().x / 2.f, window.getSize().y / 2.f);
	sf::FloatRect textRect;

	//title of the game
	title.setFont(font);
	title.setCharacterSize(45);
	title.setFillColor(sf::Color::White);
	title.setString("Fruit Ninja\n  by Matt");
	textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	title.setPosition(hfScreen + sf::Vector2f(0,-150.f));

	//"slash to start" button
	btnText.setFont(font);
	btnText.setCharacterSize(35);
	btnText.setFillColor(sf::Color(80,50,50));
	btnText.setString("Slash to start");
	textRect = btnText.getLocalBounds();
	btnText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	btnText.setPosition(hfScreen + sf::Vector2f(0, 150.f));
	
	//hitbox of the button
	button.setPosition(hfScreen + sf::Vector2f(0, 150.f));
	button.setSize(sf::Vector2f(310, 80));
	button.setOrigin(button.getSize().x / 2.f, button.getSize().y / 2.f);
	button.setFillColor(sf::Color::Black);

	//graphics of the button
	buttonGfx.setTexture(btnTxt);
	buttonGfx.setScale(5.5, 2.5);
	buttonGfx.setOrigin(btnTxt.getSize().x / 2.f, btnTxt.getSize().y / 2.f);
	buttonGfx.setPosition(hfScreen + sf::Vector2f(0, 150.f));

	initalized = true;
}
void Menu::update(sf::RenderWindow& window, Slash& slash) {
	if (!initalized) {
		std::cerr << "you must initalize Menu" << std::endl;
		return;
	}
	
	//if you're slashing (dragging mouse) and hit the button it changes scene
	if (!slash.getSlashing()) {
		return;
	}

	sf::Vector2f slashPos = slash.getHead().getPosition();

	//aabb collision checker
	if(checkAABB(slashPos, button)){
		changeScene(1);
	}
}

void Menu::display(sf::RenderWindow& window) {
	if (!initalized) {
		std::cerr << "you must initalize Menu" << std::endl;
		return;
		return;
	}

	//print title and button
	window.draw(title);
	window.draw(buttonGfx);
	window.draw(btnText);
	//hitbox of the button
	//window.draw(button);
}