#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Shapes {
	class CircleEntity : public sf::CircleShape	{
	private:
		sf::Vector2f acceleration{ 0.0f, 0.0f };
		sf::Vector2f velocity{ 0.0f, 0.0f };
		float mass = 1;

	public:
		using CircleShape::CircleShape;

		CircleEntity();

		sf::Vector2f getAcceleration();
		void setAcceleration(const sf::Vector2f& accel);

		sf::Vector2f getVelocity();
		void setVelocity(const sf::Vector2f& vel);

		float getMass();
		void setMass(const float& m);
	};
}