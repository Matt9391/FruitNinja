#include <iostream>
#include "Fruit.h"
#include "Functions.h"

Fruit::Fruit(sf::Vector2f pos, sf::Vector2f speed, float radius, sf::Vector2f targetPos, sf::Texture& txt, std::vector<sf::Texture*> hTxts) :
	Entity(pos, speed, radius, targetPos, txt),
	hTxts(hTxts)
{}


void Fruit::update(sf::RenderWindow& window,sf::CircleShape circle) {
	//method that rotate the GFX	
	rotateSprite();

	outOfBound(window);

	//check collision with cursor
	if (checkSlashCollision(circle)) {
		//set the fruit to have to remove
		this->toRemove = true;
		//set the fruit to slashed
		this->slashed = true;

		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		
		//angle between fruit and mouse to make the right cut angle
		//sometimes doesnt work :)
		float angle = atan2(mousePos.y - this->pos.y, mousePos.x - this->pos.x);
	
		//method that spawn 2 half of the fruit
		spawnHalf(this->pos, this->radius, angle, this->hTxts);
		
		//slash sound effect
		Slash::SlashSoundPlay();
	}

	//gravity on the fruit
	addGravity();

	//adding velocity to pos
	this->pos += this->velocity;
}
