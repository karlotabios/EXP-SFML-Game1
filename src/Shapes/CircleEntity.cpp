#include "../Globals/defaults.h"
#include "../Utils/print.h"

#include "CircleEntity.h"
#include <algorithm>
#include <iostream>

namespace kt::Shapes {
	CircleEntity::CircleEntity() : CircleShape() {
		setRadius(100.0f);
		setOrigin(sf::Vector2f(getRadius(), getRadius()));
		setFillColor(sf::Color::Red);
		setOutlineColor(sf::Color::Red);
		setOutlineThickness(1.0f);

		// Temporary initial velocity
		addForce(sf::Vector2f{ 100000.0f, -100000.0f });
	}

	void CircleEntity::move(const sf::Time& deltaTime, bool isFrictionEnabled) {
		sf::Vector2f acceleration = this->getAcceleration();
		sf::Vector2f velocity = this->getVelocity();
		sf::Vector2f position = this->getPosition();
		sf::Vector2f netForce{};
		float mass = this->getMass();

		// F_net = sum(F_0, F_1, ... F_N)
		if (m_forces.size() != 0) {
			for (auto& force : m_forces) {
				netForce += force;
			}
		}
		else {
			acceleration = sf::Vector2f{ 0.0f, 0.0f };
		}

		if (velocity.length() == 0) {
			m_isMoving = false;
			std::cout << "[INFO/isMoving] m_isMoving = false; m_isMoving ==> " << m_isMoving << std::endl;
		}
		else {
			m_isMoving = true;
			std::cout << "[INFO/isMoving] m_isMoving = true; m_isMoving ==> " << m_isMoving << std::endl;
		}

		sf::Vector2f frictionForce{};
		sf::Vector2f frictionDirection;

		const float timeSquared = deltaTime.asSeconds() * deltaTime.asSeconds();

		if (isFrictionEnabled) {
			// hypothetical normal force, the floor is the screen below all drawn objects
			const float normalForceMagnitude = kt::Globals::GRAVITY_ACCELERATION * mass;
			const float staticFrictionMagnitude = kt::Globals::STATIC_FRICTION_COEF * normalForceMagnitude;
			const float kineticFrictionMagnitude = kt::Globals::KINETIC_FRICTION_COEF * normalForceMagnitude;

			if (m_isMoving) {
				std::cout << "[INFO/kinetic friction] Circle is moving, kinetic friction here!" << std::endl;
				frictionDirection = -velocity.normalized();
				frictionForce = kineticFrictionMagnitude * frictionDirection;
				sf::Vector2f frictionAcceleration = frictionForce / mass;
				std::cout << "[INFO/kinetic friction] velocity.length() ==> " << velocity.length() << std::endl;
				std::cout << "[INFO/kinetic friction] frictionAcceleration.length() ==> " << frictionAcceleration.length() << std::endl;
				if (velocity.length() <= (frictionAcceleration.length() * deltaTime.asSeconds())) {
					velocity = { 0.0f, 0.0f };
				}
				else {
					velocity = velocity + (frictionAcceleration * deltaTime.asSeconds());
				}
			}
			else {
				if (netForce.length() != 0) {
					std::cout << "[INFO/static friction] netForce.length() is non-zero!" << std::endl;
					frictionDirection = -netForce.normalized();
					std::cout << "[INFO/static friction] frictionDirection.normalized().x ==> " << frictionDirection.normalized().x << std::endl;
					std::cout << "[INFO/static friction] frictionDirection.normalized().y ==> " << frictionDirection.normalized().y << std::endl;
				}
				frictionForce = staticFrictionMagnitude * frictionDirection;

				if (netForce.length() <= staticFrictionMagnitude) {
					std::cout << "[INFO/static friction] Can't escape static friction!" << std::endl;
					std::cout << "[INFO/static friction] netForce.length() ==> " << netForce.length() << std::endl;
					std::cout << "[INFO/static friction] staticFrictionMagnitude ==> " << staticFrictionMagnitude << std::endl;
					netForce = { 0.0f, 0.0f };
				}
				else {
					std::cout << "[INFO/static friction] Circle escaped static friction!" << std::endl;
					std::cout << "[INFO/static friction] netForce.length() ==> " << netForce.length() << std::endl;
					std::cout << "[INFO/static friction] staticFrictionMagnitude ==> " << staticFrictionMagnitude << std::endl;
					std::cout << "[INFO/static friction] frictionForce.normalized().x ==> " << frictionForce.normalized().x << std::endl;
					std::cout << "[INFO/static friction] frictionForce.normalized().y ==> " << frictionForce.normalized().y << std::endl;
					netForce -= frictionForce;
				}
			}
		}

		if (netForce.length() != 0)	{
			std::cout << "[INFO/Net Force] netForce.length() is non-zero!" << std::endl;
			std::cout << "[INFO/Net Force] netForce.length() ==> " << netForce.length() << std::endl;
			std::cout << "[INFO/Net Force] netForce.normalized().x ==> " << netForce.normalized().x << std::endl;
			std::cout << "[INFO/Net Force] netForce.normalized().y ==> " << netForce.normalized().y << std::endl;
		}
		else {
			std::cout << "[INFO/Net Force] netForce.length() is zero!" << std::endl;
		}
		
		acceleration += (netForce / mass);
		std::cout << "[INFO/acceleration] acceleration.x ==> " << acceleration.x << std::endl;
		std::cout << "[INFO/acceleration] acceleration.y ==> " << acceleration.y << std::endl;

		// kinematics equation:
		// x_f = x_0 + (v_0 * t) + ((a * t^2) / 2)
		position = position + (velocity * deltaTime.asSeconds()) + ((acceleration * timeSquared) / 2.0f);

		// kinematics equation:
		// v_f = v_0 + at
		velocity = velocity + (acceleration * deltaTime.asSeconds());

		if (velocity.length() != 0) {
			std::cout << "[INFO/velocity] velocity.normalized();" << std::endl;
			std::cout << "[INFO/velocity] velocity.normalized().x ==> " << velocity.normalized().x << std::endl;
			std::cout << "[INFO/velocity] velocity.normalized().y ==> " << velocity.normalized().y << std::endl;
		}

		this->setVelocity(velocity);
		this->setPosition(position);

		m_forces.clear();
		return;
	}

	bool CircleEntity::isMoving() const {
		return m_isMoving;
	}

	void CircleEntity::addForce(const sf::Vector2f appliedForce) {
		m_forces.push_back(appliedForce);
		return;
	}

	void CircleEntity::makeTransparent() {
		sf::Color color;
		color = this->getFillColor();
		color.a = 100;
		this->setFillColor(color);
		color = this->getOutlineColor();
		color.a = 100;
		this->setOutlineColor(color);
	}

	void CircleEntity::makeOpaque() {
		sf::Color color;
		color = this->getFillColor();
		color.a = 255;
		this->setFillColor(color);
		color = this->getOutlineColor();
		color.a = 100;
		this->setOutlineColor(color);
	}

	CircleEntity::~CircleEntity() {};
}