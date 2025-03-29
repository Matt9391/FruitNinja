#include <iostream>

#include "Bomb.h"
#include "Functions.h"

Bomb::Bomb(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt) :
	Entity(pos,speed,radius,targetPos,txt)
{
	//rotate angle increased
	angleInc = this->dir.x > 0 ? 4 : -4;
	//gravity reduced
	this->gravity = 0.4f;
	//gfx scaled
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
