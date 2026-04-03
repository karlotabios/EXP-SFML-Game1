#include "Movable.h"

namespace kt::Physical {
	Movable::Movable() {};

	sf::Vector2f Movable::getAcceleration() {
		return acceleration;
	}

	void Movable::setAcceleration(const sf::Vector2f& accel) {
		acceleration = accel;
	}

	sf::Vector2f Movable::getVelocity() {
		return velocity;
	}

	void Movable::setVelocity(const sf::Vector2f& vel) {
		velocity = vel;
	}

	float Movable::getMass() {
		return mass;
	}

	void Movable::setMass(const float& m) {
		mass = m;
	}

	Movable::~Movable() {};
}