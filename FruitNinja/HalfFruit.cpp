#include "HalfFruit.h"
#include "Functions.h"

HalfFruit::HalfFruit(sf::Vector2f pos, float speed, float radius, float angle, int lifespan, sf::Texture& txt, float gfxAngle) :
	pos(pos),
	speed(speed),
	radius(radius),
	lifespan(lifespan),
	toRemove(false),
	gravity(0.5)
{
	velocity = sf::Vector2f(0, 0);
	dir = sf::Vector2f(0, 0);

	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(pos);
	shape.setFillColor(sf::Color(200, 0, 100));

	setDir(angle);
	setVelocity();

	this->gfx.setTexture(txt);
	this->gfx.setScale(radius * 0.0025f, radius * 0.0025f);
	this->gfx.setOrigin(txt.getSize().x / 2.f, txt.getSize().y / 2.f);
	this->gfx.setRotation(gfxAngle);
}

void HalfFruit::addGravity() {
	this->velocity.y += this->gravity;
}

void HalfFruit::update() {
	lifespan--;
	if (lifespan < 0) {
		this->toRemove = true;
	}

	addGravity();
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
	this->gfx.setPosition(this->pos);

	//window.draw(this->shape);
	window.draw(this->gfx);
}