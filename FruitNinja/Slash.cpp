#include "Slash.h"
#include "Functions.h"
#include <iostream>

sf::Sound Slash::slashSound;
																				//triangleStrip is a type of vertex, dont care about it
Slash::Slash(sf::RenderWindow& window, sf::SoundBuffer& sb) : slashing(false), slash(sf::TriangleStrip), maxTails(9){
	//radius scaled in base of the window size
	this->radius = window.getSize().y / 27.f;
	this->slashSound.setBuffer(sb);
	this->slashSound.setVolume(20);
}

void Slash::update(sf::RenderWindow& window) {
	//update the slashing variable if the mouse is being dragged/clicked
	this->slashing = checkSlashing();

	if (!this->slashing) {
		//"slowly" reduce the circles of the array if you're not slashing
		if (this->circles.size() > 0) {
			this->circles.erase(this->circles.begin());
		}
		else {
			this->circles.clear();
			this->slash.clear();
		}
		//move the slash, so update the slash if you got more that one circle
		//you need at least 2 circle to create the slash because it use 'i' and 'i+1'
		if (this->circles.size() > 1) {
			moveSlash();
		}

		return;
	}

	//create the new circle
	sf::CircleShape c(this->radius);

	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	sf::Vector2f spawnPos(0, 0);

	//add circle just work on his position
	if (this->circles.size() > 0) {
		addCircle(mousePos, &spawnPos);
	}
	else {
		//if its the first you can just place over the cursor
		spawnPos = mousePos;
	}

	c.setPosition(spawnPos);
	c.setFillColor(sf::Color::Red);
	c.setOrigin(this->radius, this->radius);
	circles.push_back(c);

	//keeps the cirlce in range
	if (circles.size() > this->maxTails) {
		circles.erase(circles.begin());
	}

	moveSlash();
}

//method that calculate the position of the circle when added
void Slash::addCircle(sf::Vector2f& mousePos, sf::Vector2f* spawnPos) {
	//lc = last circle
	//so last circle position and ect.
	sf::Vector2f lcPos = this->circles[this->circles.size() - 1].getPosition();
	float lcRad = this->circles[this->circles.size() - 1].getRadius();
	float minDist = lcRad * 2;

	//distance between 2 points
	float dist = distance(mousePos, lcPos);
	if (dist > minDist) {
		dist = minDist;
	}

	float angle = atan2(mousePos.y - lcPos.y, mousePos.x - lcPos.x);
	//just setting the position in realtion with the angle and the distance
	*spawnPos = sf::Vector2f(lcPos.x + dist * cos(angle), lcPos.y + dist * sin(angle));
}

//method that update the slash composed of vertex
void Slash::moveSlash() {
	//clearing the slash to start
	this->slash.clear();

	//color channel for gfx
	int alpha = 255;
	int b = 255;
	int red = 255;
	int green = 255;

	for (int i = 0; i < this->circles.size() - 1; i++) {
		sf::Vector2f c1 = this->circles[i].getPosition();
		sf::Vector2f c2 = this->circles[i + 1].getPosition();

		//dir is the vector from c1 to c2 (if i'm remember right, otherwise its reverse, from c2 to c1)
		sf::Vector2f dir = c1 - c2;

		//vector perpendicular
		//x: 0, y: 2;
		//un vector perpendicular will be (pointing left)
		//x: -2, y: 0;
		sf::Vector2f normal(-dir.y, dir.x);
		//normal of the vector
		normal = normalize(normal);

		float r = this->radius;
		//position of vertexes
		sf::Vector2f extLeft = c1 + normal * r;
		sf::Vector2f extRight = c1 - normal * r;
		sf::Vector2f extBottom = c1 + normalize(dir) * r;
		sf::Vector2f extTop = c2 - normalize(dir) * (r / 2);

		red -= 15;
		green -= 35;
		//its like a clamp, it limits the val in the bounds
		red = constrain((int)red, 0, 255);
		green = constrain((int)green, 0, 255);

		//to make the peak
		if (i == 0) {
			this->slash.append(sf::Vertex(extBottom, sf::Color(red, green, b, alpha)));
		}

		this->slash.append(sf::Vertex(extLeft, sf::Color(red, green, b, alpha)));

		//to make the tail
		if (i == this->circles.size() - 2) {
			this->slash.append(sf::Vertex(extTop, sf::Color(red, green, b, alpha)));
		}

		this->slash.append(sf::Vertex(extRight, sf::Color(red, green, b, alpha)));
	}
}


sf::CircleShape Slash::getHead() {
	if (this->circles.size() > 0) {
		return this->circles[this->circles.size() - 1];
	}
	else {
		//return a random circle with low radius 
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

void Slash::SlashSoundPlay() {
	slashSound.play();
}