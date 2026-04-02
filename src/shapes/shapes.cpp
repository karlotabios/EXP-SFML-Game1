#include <iostream>
#include "Shapes.h"

namespace kt::Shapes {
	CircleEntity::CircleEntity() : CircleShape() {
		setRadius(30.0f);
		setOrigin(sf::Vector2f(getRadius(), getRadius()));
		setFillColor(sf::Color::Red);
		setOutlineColor(sf::Color::Red);
	}

	sf::Vector2f CircleEntity::getAcceleration() {
		return acceleration;
	}
	void CircleEntity::setAcceleration(const sf::Vector2f& accel) {
		acceleration = accel;
	}

	sf::Vector2f CircleEntity::getVelocity() {
		return velocity;
	}
	void CircleEntity::setVelocity(const sf::Vector2f& vel) {
		velocity = vel;
	}

	float CircleEntity::getMass() {
		return mass;
	}
	void CircleEntity::setMass(const float& m) {
		mass = m;
	}
}