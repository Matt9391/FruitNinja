#include <iostream>

#include "UI.h"
#include "Functions.h"

int UI::score = 0;
int UI::maxScore = 0;
int UI::maxStreak = 0;
int UI::lives = 3;
int UI::alertTime = 120;
int UI::debounce = 0;

bool UI::gameOver = false;
bool UI::initalized = false;

sf::Font UI::font;
sf::Text UI::scoreText;
sf::Text UI::maxStreakText;
sf::Text UI::livesText;
sf::Text UI::alertText;

sf::Sprite UI::lifeGfx;
sf::Sprite UI::alertGfx;

sf::Sound UI::song;
bool UI::songEnable = false;

sf::Text UI::btnText;
sf::RectangleShape UI::button;
sf::Sprite UI::buttonGfx;

void UI::init(sf::RenderWindow& window, sf::Texture& lifeTxt, sf::Texture& alertTxt, sf::SoundBuffer& musicBuff, sf::Texture& btnTxt) {
	if (!font.loadFromFile("./Fonts/LazyFox Pixel Font 2.ttf")) {
		std::cerr << "Errore nel caricamento del font!" << std::endl;
		return;
	}

	//just a lot of annying things

	lifeGfx.setTexture(lifeTxt);
	lifeGfx.setOrigin(lifeTxt.getSize().x / 2.f, lifeTxt.getSize().y / 2.f);
	lifeGfx.setScale(5, 5);

	alertGfx.setTexture(alertTxt);
	alertGfx.setOrigin(alertTxt.getSize().x / 2.f, alertTxt.getSize().y / 2.f);
	alertGfx.setScale(8, 3.5);
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

	scoreText.setString(std::to_string(score));
	maxStreakText.setString(std::to_string(maxStreak));
	livesText.setString(std::to_string(lives));
	alertText.setString("Hai perso looser");

	scoreText.setPosition(sf::Vector2f(window.getSize().x / 2.f, 50));
	maxStreakText.setPosition(sf::Vector2f(window.getSize().x / 20.f, 50));
	livesText.setPosition(sf::Vector2f(window.getSize().x / 20.f, 100));
	alertText.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
	
	sf::FloatRect textRect = alertText.getLocalBounds();
	alertText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	song.setBuffer(musicBuff);
	song.setLoop(true);
	song.setVolume(5);
	song.stop();


	btnText.setFont(font);
	btnText.setCharacterSize(25);
	btnText.setFillColor(sf::Color(80, 50, 50));
	btnText.setString("Audio: ON");

	textRect = btnText.getLocalBounds();
	btnText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	btnText.setPosition(sf::Vector2f(100, window.getSize().y - 60.f));

	button.setPosition(sf::Vector2f(100, window.getSize().y - 60.f));
	button.setSize(sf::Vector2f(310, 80));
	button.setOrigin(button.getSize().x / 2.f, button.getSize().y / 2.f);
	button.setFillColor(sf::Color::Black);

	buttonGfx.setTexture(btnTxt);
	buttonGfx.setScale(2.7f, 2.5f);
	buttonGfx.setOrigin(btnTxt.getSize().x / 2.f, btnTxt.getSize().y / 2.f);
	buttonGfx.setPosition(sf::Vector2f(100, window.getSize().y - 60.f));

	gameOver = false;
	initalized = true;
}

void UI::incrementScore() {
	if (!initalized) {
		std::cerr << "you must initalize UI"<<std::endl;
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
		std::cerr << "you must initalize UI" << std::endl;
		return;
	}

	score = 0;
}

void UI::resetAll() {
	if (!initalized) {
		std::cerr << "you must initalize UI" << std::endl;
		return;
	}

	score = 0;
	maxScore = 0;
	maxStreak = 0;
	lives = 3;
	gameOver = false;
	alertTime = 120;
}

bool UI::decrementLives() {
	if (!initalized) {
		std::cerr << "you must initalize UI" << std::endl;
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

//method that show the game over panel for some second (alertime frames)
void UI::showGameOver(sf::RenderWindow& window) {
	if (!initalized) {
		std::cerr << "you must initalize UI" << std::endl;
		return;
	}

	if (!gameOver) {
		return;
	}
	
	if (alertTime < 0) {
		return;
	}

	alertTime--;

	alertText.setString("You lose! Score: " + std::to_string(maxScore));
	
	sf::FloatRect textRect = alertText.getLocalBounds();
	alertText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);

	window.draw(alertGfx);
	window.draw(alertText);

}

void UI::audioButtonHandler(sf::RenderWindow& window, Slash& slash) {
	if (!initalized) {
		std::cerr << "you must initalize UI" << std::endl;
		return;
	}

	std::string str = songEnable ? "ON" : "OFF";
	btnText.setString("Audio: " + str);
	
	sf::FloatRect textRect = btnText.getLocalBounds();
	btnText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);

	window.draw(buttonGfx);
	window.draw(btnText);
	
	debounce--;
	
	if (debounce > 0) {
		return;
	}

	if (!slash.getSlashing()) {
		return;
	}

	sf::Vector2f slashPos = slash.getHead().getPosition();

	if (checkAABB(slashPos, button)) {
		songEnable = !songEnable;
		debounce = 30;
	}

	//window.draw(button);
}

void UI::playSong() {
	if (!initalized) {
		std::cerr << "you must initalize UI" << std::endl;
		return;
	}

	if (!songEnable) {
		song.stop();
		return;
	}

	if (song.getStatus() != sf::Sound::Playing) {
		song.play();
	}
}

void UI::display(sf::RenderWindow& window) {
	if (!initalized) {
		std::cerr << "you must initalize UI" << std::endl;
		return;
	}

	sf::FloatRect textRect = scoreText.getLocalBounds();
	scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	scoreText.setPosition(sf::Vector2f(window.getSize().x / 2.f, 50));

	scoreText.setString(std::to_string(score));
	maxStreakText.setString("Top Streak: " + std::to_string(maxStreak));
	
	for (int i = 0; i < lives; i++) {
		lifeGfx.setPosition(window.getSize().x - 100.f * i - 50.f, 50.f);
		window.draw(lifeGfx);
	}

	window.draw(scoreText);
	window.draw(maxStreakText);
}