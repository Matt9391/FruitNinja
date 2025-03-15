#include <iostream>

#include "Bomb.h"
#include "Functions.h"

Bomb::Bomb(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos) : 
	Entity(pos,speed,radius,targetPos)
{}

void Bomb::update(sf::RenderWindow& window, sf::CircleShape circle) {
	outOfBound(window);
	if (checkSlashCollision(circle)) {
		this->toRemove = true;
		this->slashed = true;
	}
	addGravity();

	this->pos += this->velocity;
}


void Bomb::display(sf::RenderWindow& window) {
	this->shape.setPosition(this->pos);
	this->shape.setFillColor(sf::Color(0, 0, 100));

	window.draw(this->shape);
}