#include "HalfFruit.h"

HalfFruit::HalfFruit(sf::Vector2f pos, float speed, float radius, float angle, int lifespan) :
	pos(pos),
	speed(speed),
	radius(radius),
	lifespan(lifespan),
	toRemove(false)
{
	velocity = sf::Vector2f(0, 0);
	dir = sf::Vector2f(0, 0);

	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(pos);
	shape.setFillColor(sf::Color(200, 0, 100));

	setDir(angle);
	setVelocity();
}

void HalfFruit::update() {
	lifespan--;
	if (lifespan < 0) {
		this->toRemove = true;
	}

	this->pos += this->velocity;
}


void HalfFruit::setDir(float angle) {
	this->dir.x = cos(angle);
	this->dir.y = sin(angle);
}

void HalfFruit::setVelocity() {
	this->velocity = sf::Vector2f(this->speed * this->dir.x, this->speed * this->dir.y);
}

void HalfFruit::display(sf::RenderWindow& window) {
	this->shape.setPosition(this->pos);

	window.draw(this->shape);
}