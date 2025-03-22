#include "Slash.h"
#include "Functions.h"
#include <iostream>

Slash::Slash(sf::RenderWindow& window) : slashing(false), slash(sf::TriangleStrip), maxTails(9){
	this->radius = window.getSize().y / 27;
}

void Slash::update(sf::RenderWindow& window) {
	this->slashing = checkSlashing();

	if (!this->slashing) {
		if (this->circles.size() > 0) {
			this->circles.erase(this->circles.begin());
		}
		else {
			this->circles.clear();
			this->slash.clear();
		}
		if (this->circles.size() > 1) {
			moveSlash();
		}

		return;
	}

	

	sf::CircleShape c(this->radius);

	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::Vector2f spawnPos(0, 0);

	if (this->circles.size() > 0) {
		addCircle(mousePos, &spawnPos);
	}
	else {
		spawnPos = mousePos;
	}

	c.setPosition(spawnPos);
	c.setFillColor(sf::Color::Red);
	c.setOrigin(this->radius, this->radius);
	circles.push_back(c);

	if (circles.size() > this->maxTails) {
		circles.erase(circles.begin());
	}
	moveSlash();
}

void Slash::addCircle(sf::Vector2f& mousePos, sf::Vector2f* spawnPos) {
	sf::Vector2f lcPos = this->circles[this->circles.size() - 1].getPosition();
	float lcRad = this->circles[this->circles.size() - 1].getRadius();
	float minDist = lcRad * 2;

	float dist = distance(mousePos, lcPos);
	if (dist < minDist) {
		minDist = dist;
	}
	else {
		dist = minDist;
	}

	float angle = atan2(mousePos.y - lcPos.y, mousePos.x - lcPos.x);
	*spawnPos = sf::Vector2f(lcPos.x + dist * cos(angle), lcPos.y + dist * sin(angle));
}

void Slash::moveSlash() {
	this->slash.clear();

	int alpha = 255;
	int b = 255;
	int red = 255;
	int green = 255;

	for (int i = 0; i < this->circles.size() - 1; i++) {
		sf::Vector2f c1 = this->circles[i].getPosition();
		sf::Vector2f c2 = this->circles[i + 1].getPosition();

		sf::Vector2f dir = c1 - c2;

		//vettore perdendicolare
		//x: 0, y: 2;
		//un v perdendicolare sarà (verso sinistra)
		//x: -2. y: 0;
		sf::Vector2f normal(-dir.y, dir.x);
		//normalizzazione vettore
		normal = normalize(normal);

		float r = this->radius;
		sf::Vector2f extLeft = c1 + normal * r;
		sf::Vector2f extRight = c1 - normal * r;
		sf::Vector2f extBottom = c1 + normalize(dir) * r;
		sf::Vector2f extTop = c2 - normalize(dir) * (r / 2);

		red -= 15;
		green -= 35;
		red = constrain((int)red, 0, 255);
		green = constrain((int)green, 0, 255);


		if (i == 0) {
			this->slash.append(sf::Vertex(extBottom, sf::Color(red, green, b, alpha)));
		}
		else if (i == this->circles.size() - 2) {
			this->slash.append(sf::Vertex(extTop, sf::Color(red, green, b, alpha)));
		}

		this->slash.append(sf::Vertex(extLeft, sf::Color(red, green, b, alpha)));
		this->slash.append(sf::Vertex(extRight, sf::Color(red, green, b, alpha)));
	}
}

sf::CircleShape Slash::getHead() {
	if (this->circles.size() > 0) {
		return this->circles[this->circles.size() - 1];
	}
	else {
		sf::CircleShape c(2);
		return c;
	}
}

bool Slash::getSlashing() {
	return this->slashing;
}

bool Slash::checkSlashing() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Slash::display(sf::RenderWindow& window) {

	//for (sf::CircleShape c : this->circles) {
	//		window.draw(c);
	//}
	//if (this->circles.size() > 0) {
	//	window.draw(this->circles[this->circles.size()-1]);
	//}
	window.draw(this->slash);

}