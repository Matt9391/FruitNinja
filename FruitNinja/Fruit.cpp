#include <iostream>
#include "Fruit.h"
#include "Functions.h"

Fruit::Fruit(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt, std::vector<sf::Texture*> hTxts) :
	Entity(pos, speed, radius, targetPos, txt),
	hTxts(hTxts)
{}


void Fruit::update(sf::RenderWindow& window,sf::CircleShape circle) {
	rotateSprite();

	outOfBound(window);
	if (checkSlashCollision(circle)) {
		this->toRemove = true;
		this->slashed = true;
		std::cout << "COLLIDO" << std::endl;
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		//float angle = atan2(this->pos.y - mousePos.y, this->pos.x - mousePos.x);
		float angle = atan2(mousePos.y - this->pos.y, mousePos.x - this->pos.x);
		spawnHalf(this->pos, this->radius, angle, this->hTxts);
	}
	addGravity();

	this->pos += this->velocity;
}


//void Fruit::display(sf::RenderWindow& window) {
//	this->shape.setPosition(this->pos);
//	
//	window.draw(this->shape);
//}