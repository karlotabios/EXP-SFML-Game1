#include "Movable.h"

namespace kt::Physical {
	Movable::Movable() {};

	sf::Vector2f Movable::getAcceleration() {
		return m_acceleration;
	}

	void Movable::setAcceleration(const sf::Vector2f& accel) {
		m_acceleration = accel;
	}

	sf::Vector2f Movable::getVelocity() {
		return m_velocity;
	}

	void Movable::setVelocity(const sf::Vector2f& vel) {
		m_velocity = vel;
	}

	float Movable::getMass() {
		return m_mass;
	}

	void Movable::setMass(const float& m) {
		m_mass = m;
	}

	Movable::~Movable() {};
}