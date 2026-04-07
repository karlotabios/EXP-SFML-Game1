#include "CircleEntity.h"
#include "../Physical/Movable.h"

namespace kt::Shapes {
	CircleEntity::CircleEntity() : CircleShape() {
		setRadius(150.0f);
		setOrigin(sf::Vector2f(getRadius(), getRadius()));
		setFillColor(sf::Color::Red);
		setOutlineColor(sf::Color::Red);
	}

	void CircleEntity::move() {
		sf::Vector2f acceleration = this->getAcceleration();
		sf::Vector2f velocity = this->getVelocity();
		sf::Vector2f position = this->getPosition();
		velocity += acceleration;
		position += velocity;
		this->setVelocity(velocity);
		this->setPosition(position);
		return;
	}

	CircleEntity::~CircleEntity() {};
}