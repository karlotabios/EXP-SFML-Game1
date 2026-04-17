#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Physical {
	class Movable {
	private:
		sf::Vector2f m_acceleration{ 0.0f, 0.0f };
		sf::Vector2f m_velocity{ 0.0f, 0.0f };
		float m_mass = 1;

	protected:
		std::vector<sf::Vector2f> m_forces;

	public:
		Movable();

		virtual sf::Vector2f getAcceleration();
		virtual void setAcceleration(const sf::Vector2f& accel);

		virtual sf::Vector2f getVelocity();
		virtual void setVelocity(const sf::Vector2f& vel);

		virtual float getMass();
		virtual void setMass(const float& m);

		virtual void clearForces();

		virtual ~Movable();
	};
}