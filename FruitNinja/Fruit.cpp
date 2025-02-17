#include <iostream>
#include "Fruit.h"
#include "Functions.h"

Fruit::Fruit(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::RenderWindow &window) : 
	pos(pos), 
	speed(speed), 
	radius(radius), 
	gravity(0.5), 
	toRemove(false)
{
	velocity = sf::Vector2f(0, 0);
	dir = sf::Vector2f(0, 0);

	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(pos);

	setDir(sf::Vector2f((float)window.getSize().x/2, (float)window.getSize().y/2));
	setVelocity();
}

void Fruit::setVelocity() {
	this->velocity = sf::Vector2f(this->speed.x * this->dir.x, this->speed.y * this->dir.y);
}

void Fruit::addGravity() {
	this->velocity.y += this->gravity;
}

//Funzione che setta la direzione rispetto a una posizione finale
//tutte le funzioni matematiche di C++ vanno in radianti
void Fruit::setDir(sf::Vector2f targetPos) {
	//in radianti
	float angle = std::atan2(targetPos.y - this->pos.y, targetPos.x - this->pos.x);
	
	this->dir.x = cos(angle);
	this->dir.y = -1;
}

void Fruit::outOfBound() {
	if (this->pos.y > 800) {
		this->toRemove = true;
	}
}

void Fruit::update() {
	outOfBound();
	
	addGravity();

	this->pos += this->velocity;
}

void Fruit::display(sf::RenderWindow& window) {
	this->shape.setPosition(this->pos);

	this->shape.setFillColor(sf::Color(100, 0, 100));
	window.draw(this->shape);
}