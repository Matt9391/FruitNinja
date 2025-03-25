#include <iostream>

#include "Bomb.h"
#include "Functions.h"

Bomb::Bomb(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt) :
	Entity(pos,speed,radius,targetPos,txt)
{
	angleInc = this->dir.x > 0 ? 4 : -4;
	this->gravity = 0.4;
	gfx.setScale(radius * 0.0090f, radius * 0.0090f);
	gfx.setOrigin(txt.getSize().x / 2.f - radius * 0.2f, txt.getSize().y / 2.f + radius / 1.7f);
}

void Bomb::update(sf::RenderWindow& window, sf::CircleShape circle) {
	rotateSprite();

	outOfBound(window);
	if (checkSlashCollision(circle)) {
		this->toRemove = true;
		this->slashed = true;
	}
	addGravity();

	this->pos += this->velocity;
}


//void Bomb::display(sf::RenderWindow& window) {
//	this->shape.setPosition(this->pos);
//	this->shape.setFillColor(sf::Color(0, 0, 100));
//
//	window.draw(this->shape);
//}