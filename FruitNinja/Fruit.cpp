#include <iostream>
#include "Fruit.h"
#include "Functions.h"

Fruit::Fruit(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos) : 
	pos(pos), 
	speed(speed), 
	radius(radius), 
	gravity(0.5), 
	toRemove(false),
	slashed(false)
{
	velocity = sf::Vector2f(0, 0);
	dir = sf::Vector2f(0, 0);

	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(pos);
	shape.setFillColor(sf::Color(100, 0, 100));

	setDir(targetPos);
	setVelocity();
}

void Fruit::checkSlashCollision(sf::RenderWindow& w, sf::CircleShape& circle) {
	if (circle.getRadius() <= 2) {
		return;
	}

	if (checkCircleCollision(this->shape, circle)) {
		this->toRemove = true;
		this->slashed = true;
		std::cout << "COLLIDO" << std::endl;
		sf::Vector2f mousePos = w.mapPixelToCoords(sf::Mouse::getPosition(w));
		//float angle = atan2(this->pos.y - mousePos.y, this->pos.x - mousePos.x);
		float angle = atan2(mousePos.y - this->pos.y, mousePos.x - this->pos.x);
		spawnHalf(this->pos,this->radius,angle);
	}
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

void Fruit::outOfBound(sf::RenderWindow& w) {
	if (this->pos.y > w.getSize().y * 1.5) {
		std::cout << "ESPLODO" << std::endl;
		this->toRemove = true;
	}
}

void Fruit::update(sf::RenderWindow& w,sf::CircleShape circle) {
	outOfBound(w);
	checkSlashCollision(w,circle);
	addGravity();

	this->pos += this->velocity;
}

void Fruit::display(sf::RenderWindow& window) {
	this->shape.setPosition(this->pos);

	window.draw(this->shape);
}