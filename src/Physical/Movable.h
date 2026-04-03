#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Physical {
	class Movable {
	private:
		sf::Vector2f acceleration{ 0.0f, 0.0f };
		sf::Vector2f velocity{ 0.0f, 0.0f };
		float mass = 1;

	public:
		Movable();

		virtual sf::Vector2f getAcceleration();
		virtual void setAcceleration(const sf::Vector2f& accel);

		virtual sf::Vector2f getVelocity();
		virtual void setVelocity(const sf::Vector2f& vel);

		virtual float getMass();
		virtual void setMass(const float& m);

		virtual ~Movable();
	};
}