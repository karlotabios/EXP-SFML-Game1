#pragma once

#include <SFML/Graphics.hpp>

#include "../Physical/Movable.h"

namespace kt::Shapes {
	class CircleEntity : public sf::CircleShape, public kt::Physical::Movable {
	private:
		sf::Vector2f acceleration{ 0.0f, 0.0f };
		sf::Vector2f velocity{ 0.0f, 0.0f };
		float mass = 1;

	public:
		using CircleShape::CircleShape;

		CircleEntity();

		template <typename T>
		bool contains(const sf::Vector2<T> point) const {
			sf::Vector2f floatPoint(static_cast<float>(point.x), static_cast<float>(point.y));
			
			sf::Vector2f vectorDistance = getPosition() - floatPoint;
			float length = vectorDistance.length(); // sqrt(x * x + y * y)
			if (length <= getRadius()) {
				return true;
			}
			return false;
		}
	};
}