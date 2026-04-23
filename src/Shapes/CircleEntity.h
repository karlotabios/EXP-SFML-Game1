#pragma once

#include <SFML/Graphics.hpp>
#include "../Physical/Movable.h"

namespace kt::Shapes {
	class CircleEntity : public sf::CircleShape, public kt::Physical::Movable {
	private:
		bool m_isMoving = false;

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

		void move(const sf::Time& deltaTime, bool isFrictionEnabled);
		bool isMoving() const;
		void addForce(const sf::Vector2f appliedForce);
		void makeTransparent();
		void makeOpaque();

		virtual ~CircleEntity();
	};
}