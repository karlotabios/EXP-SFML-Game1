#include "Math.h"

#include "../Globals/color.h"

namespace kt::Utils {
	std::optional<CollisionData> detectCollision(const kt::Shapes::RectangleEntity& rectangle, const kt::Shapes::CircleEntity& circle) {
		// Capture the point within the rectangle that is nearest to the circle
		sf::Vector2f nearestPoint{};

		const float xMin = rectangle.getPosition().x - (rectangle.getSize().x / 2.0f);
		const float xMax = rectangle.getPosition().x + (rectangle.getSize().x / 2.0f);
		const float yMin = rectangle.getPosition().y - (rectangle.getSize().y / 2.0f);
		const float yMax = rectangle.getPosition().y + (rectangle.getSize().y / 2.0f);

		nearestPoint.x = std::clamp(circle.getPosition().x, xMin, xMax);
		nearestPoint.y = std::clamp(circle.getPosition().y, yMin, yMax);

		sf::Vector2f distanceVector = nearestPoint - circle.getPosition();

		std::cout << "[INFO/Collision] distanceVector.x: " << distanceVector.x << std::endl;
		std::cout << "[INFO/Collision] distanceVector.y: " << distanceVector.y << std::endl;

		// If the distance to the circle from the nearest point within the rectangle is less than the radius of the circle, then there is collision
		if (distanceVector.length() < circle.getRadius()) {
			std::cout << kt::Globals::COUT_RED << "[INFO/Collision] Collision detected!!" << kt::Globals::COUT_DEFAULT << std::endl;

			float overlapMagnitude = 0;

			// Check if the circle's origin is inside the rectangle
			if (distanceVector.length() == 0) {
				// Get all nearest points on each edge of the rectangle
				const sf::Vector2f nearestTop{ circle.getPosition().x, yMin };
				const sf::Vector2f nearestRight{ xMax, circle.getPosition().y };
				const sf::Vector2f nearestBottom{ circle.getPosition().x, yMax };
				const sf::Vector2f nearestLeft{ xMin, circle.getPosition().y };

				// Get the nearest point from each edge
				const float minimumDistance = std::min({ nearestTop.length(), nearestRight.length(), nearestBottom.length(), nearestLeft.length() });

				sf::Vector2f collisionNormalDirection{};

				if (minimumDistance == nearestTop.length()) {
					collisionNormalDirection = sf::Vector2f{ 0.0f, -1.0f };
					overlapMagnitude = circle.getPosition().y - yMin + circle.getRadius();
				}
				if (minimumDistance == nearestRight.length()) {
					collisionNormalDirection = sf::Vector2f{ 1.0f, 0.0f };
					overlapMagnitude = xMax - circle.getPosition().x + circle.getRadius();
				}
				if (minimumDistance == nearestBottom.length()) {
					collisionNormalDirection = sf::Vector2f{ 0.0f, 1.0f };
					overlapMagnitude = yMax - circle.getPosition().y + circle.getRadius();
				}
				if (minimumDistance == nearestLeft.length()) {
					collisionNormalDirection = sf::Vector2f{ -1.0f, 0.0f };
					overlapMagnitude = circle.getPosition().x - xMin + circle.getRadius();
				}

				std::cout << "[INFO/Collision] collisionNormalDirection.x: " << collisionNormalDirection.x << std::endl;
				std::cout << "[INFO/Collision] collisionNormalDirection.y: " << collisionNormalDirection.y << std::endl;
				std::cout << "[INFO/Collision] overlapMagnitude: " << overlapMagnitude << std::endl;

				return CollisionData{
					collisionNormalDirection,
					overlapMagnitude
				};
			}

			overlapMagnitude = circle.getRadius() - distanceVector.length();

			std::cout << "[INFO/Collision] -(distanceVector.normalized()).x: " << -(distanceVector.normalized()).x << std::endl;
			std::cout << "[INFO/Collision] -(distanceVector.normalized()).y: " << -(distanceVector.normalized()).y << std::endl;
			std::cout << "[INFO/Collision] overlapMagnitude: " << overlapMagnitude << std::endl;

			return CollisionData{
				-(distanceVector.normalized()),
				overlapMagnitude
			};
		}
			
		return std::nullopt;
	}

	// TODO: Create templated version of detectCollision() or some overloads for different scenarios.
}