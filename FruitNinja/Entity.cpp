#include <iostream>
#include "Functions.h"
#include "Entity.h" 

Entity::Entity(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt) :
	pos(pos),
	speed(speed),
	radius(radius),
	gravity(0.5),
	toRemove(false),
	slashed(false),
	txt(txt),
	angle(0),
	angleInc(0)
{
	velocity = sf::Vector2f(0, 0);
	dir = sf::Vector2f(0, 0);

	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(pos);
	shape.setFillColor(sf::Color(100, 0, 100));

	setDir(targetPos);
	setVelocity();

	angleInc = this->dir.x > 0 ? 2 : -2;

	gfx.setTexture(txt);
	gfx.setScale(radius * 0.0025f, radius * 0.0025f);
	gfx.setOrigin(txt.getSize().x / 2.f, txt.getSize().y / 2.f);
}

void Entity::setVelocity() {
	this->velocity = sf::Vector2f(this->speed.x * this->dir.x, this->speed.y * this->dir.y);
}

//Funzione che setta la direzione rispetto a una posizione finale
//tutte le funzioni matematiche di C++ vanno in radianti
void Entity::setDir(sf::Vector2f targetPos) {
	//in radianti
	float angle = std::atan2(targetPos.y - this->pos.y, targetPos.x - this->pos.x);

	this->dir.x = cos(angle);
	this->dir.y = -1;
}

void Entity::addGravity() {
	this->velocity.y += this->gravity;
}


void Entity::outOfBound(sf::RenderWindow& window) {
	if (this->pos.y > window.getSize().y * 1.5) {
		std::cout << "ESPLODO" << std::endl;
		this->toRemove = true;
	}
}

bool Entity::checkSlashCollision(sf::CircleShape& circle) {
	if (circle.getRadius() <= 2) {
		return false;
	}

	if (checkCircleCollision(this->shape, circle)) {
		return true;
	}

	return false;
	
}

void Entity::rotateSprite() {
	this->angle += this->angleInc;
	this->gfx.setRotation(this->angle);
}


void Entity::update(sf::RenderWindow& window,sf::CircleShape circle) {
	rotateSprite();

	outOfBound(window);
	if (checkSlashCollision(circle)) {
		this->toRemove = true;
	}
	addGravity();

	this->pos += this->velocity;
}

void Entity::display(sf::RenderWindow& window) {
	this->shape.setPosition(this->pos);
	this->gfx.setPosition(this->pos);

	//window.draw(this->shape);
	window.draw(this->gfx);
}