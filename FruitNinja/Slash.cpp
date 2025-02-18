#include "Slash.h"
#include "Functions.h"
#include <iostream>

Slash::Slash() : slashing(false), slash(sf::TriangleStrip){
	
}

void Slash::update(sf::RenderWindow& window) {
	this->slashing = checkSlashing();
	this->slash.clear();

	if (!this->slashing) {
		this->circles.clear();
		return;
	}


	sf::CircleShape c(15);

	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	c.setPosition(mousePos);
	c.setFillColor(sf::Color::Red);
	c.setOrigin(15, 15);
	circles.push_back(c);

	if (circles.size() > 7) {
		circles.erase(circles.begin() );
	}

	int alpha = 180;
	
	for (int i = 0; i < this->circles.size() - 1; i++) {
		sf::Vector2f c1 = this->circles[i].getPosition();
		sf::Vector2f c2 = this->circles[i+1].getPosition();

		sf::Vector2f dir = c1 - c2;

		//vettore perdendicolare
		//x: 0, y: 2;
		//un v perdendicolare sarà (verso sinistra)
		//x: -2. y: 0;
		sf::Vector2f normal(-dir.y, dir.x);
		//normalizzazione vettore
		normal = normalize(normal);

		float r = 15;
		sf::Vector2f extLeft = c1 + normal * r;
		sf::Vector2f extRight = c1 - normal * r;
		sf::Vector2f extBottom = c1 + normalize(dir) * r;
		sf::Vector2f extTop = c2 - normalize(dir) * (r/2);

		if (i == 0) {
			this->slash.append(sf::Vertex(extBottom, sf::Color(255, 255, 255, alpha)));
		}
		else if (i == this->circles.size() - 2) {
			this->slash.append(sf::Vertex(extTop, sf::Color(255, 255, 255, alpha)));
		}

		this->slash.append(sf::Vertex(extLeft, sf::Color(255,255,255, alpha)));
		this->slash.append(sf::Vertex(extRight, sf::Color(255,255,255, alpha)));

		alpha += 25;
		alpha = constrain(alpha, 0, 255);
	}
}

bool Slash::checkSlashing() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Slash::display(sf::RenderWindow& window) {

	//for (sf::CircleShape c : this->circles) {
	//		window.draw(c);
	//}

	window.draw(this->slash);
}