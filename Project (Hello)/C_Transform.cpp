#include "C_Transform.h"

C_Transform::C_Transform(Object* owner)
	: Component(owner), position(0.0f, 0.0f)
{
}

void C_Transform::setPosition(float x, float y) {
	position = sf::Vector2f(x, y);
}

void C_Transform::setPosition(sf::Vector2f pos) {
	position = pos;
}

void C_Transform::addPosition(float x, float y) {
	position += sf::Vector2f(x, y);
}

void C_Transform::addPosition(sf::Vector2f pos) {
	position += pos;
}

void C_Transform::setX(float x) {
	position.x = x;
}

void C_Transform::setY(float y) {
	position.y = y;
}

void C_Transform::addX(float x) {
	position.x += x;
}

void C_Transform::addY(float y) {
	position.y += y;
}

const sf::Vector2f& C_Transform::getPosition() const {
	return position;
}


