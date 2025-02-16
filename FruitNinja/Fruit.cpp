#include "Fruit.h"

Fruit::Fruit(sf::Vector2f pos, float speed, float radius) : pos(pos), speed(speed), radius(radius) {
	velocity = sf::Vector2f(0, 0);

	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(pos);


}

void Fruit::update() {

}

void Fruit::display(sf::RenderWindow& window) {
	window.draw(this->shape);
}