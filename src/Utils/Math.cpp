#include "Math.h"

namespace kt::Utils {
	std::optional<sf::Vector2f> detectCollision(const kt::Shapes::RectangleEntity& rectangle, const kt::Shapes::CircleEntity& circle) {
		sf::Vector2f collisionNormal{};
		sf::Vector2f rectangleSize = rectangle.getSize();
		sf::Vector2f rectanglePosition = rectangle.getPosition();
		sf::Vector2f circlePosition = circle.getPosition();
		const float circleRadius = circle.getRadius();


		// TODO: Implementation

		// Check in X-axis
		

		// Check in Y-axis
		
		return std::nullopt;
	}

	// TODO: Create templated version of detectCollision() or some overloads for different scenarios.
}