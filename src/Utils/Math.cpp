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

		sf::Vector2f distanceVector = circle.getPosition() - nearestPoint;

		// If the distance to the circle from the nearest point within the rectangle is less than the radius of the circle, then there is collision
		if (distanceVector.length() < circle.getRadius()) {
			float overlapMagnitude = 0;

			// Case 1: If circle's origin is within the area of the rectangle, then nearestPoint will be the position of the circle itself which will result in a division by zero in vector normalization (wrong). Instead get the points on the edge of the rectangle that are nearest to the circle's position, and compute the normal and magnitude of overlap from there.
			// Check if the circle's origin is inside the rectangle
			if (distanceVector.length() == 0) {
				// Get all nearest points on each edge of the rectangle
				const sf::Vector2f nearestTop{ circle.getPosition().x, yMin };
				const sf::Vector2f nearestRight{ xMax, circle.getPosition().y };
				const sf::Vector2f nearestBottom{ circle.getPosition().x, yMax };
				const sf::Vector2f nearestLeft{ xMin, circle.getPosition().y };

				const float distanceTop = (nearestTop - circle.getPosition()).length();
				const float distanceRight = (nearestRight - circle.getPosition()).length();
				const float distanceBottom = (nearestBottom - circle.getPosition()).length();
				const float distanceLeft = (nearestLeft - circle.getPosition()).length();

				// Get the distance to the nearest point on the edges
				float minimumDistance = std::min({ distanceTop, distanceRight, distanceBottom, distanceLeft });

				sf::Vector2f collisionNormalDirection{};

				if (minimumDistance == distanceTop) {
					collisionNormalDirection = sf::Vector2f{ 0.0f, -1.0f };
					overlapMagnitude = circle.getPosition().y - yMin + circle.getRadius();
				}
				else if (minimumDistance == distanceRight) {
					collisionNormalDirection = sf::Vector2f{ 1.0f, 0.0f };
					overlapMagnitude = xMax - circle.getPosition().x + circle.getRadius();
				}
				else if (minimumDistance == distanceBottom) {
					collisionNormalDirection = sf::Vector2f{ 0.0f, 1.0f };
					overlapMagnitude = yMax - circle.getPosition().y + circle.getRadius();
				}
				else if (minimumDistance == distanceLeft) {
					collisionNormalDirection = sf::Vector2f{ -1.0f, 0.0f };
					overlapMagnitude = circle.getPosition().x - xMin + circle.getRadius();
				}

				return CollisionData{
					collisionNormalDirection,
					overlapMagnitude
				};
			}
			// Case 2: If the circle's origin is outside the rectangle, then simply get the direction from the nearestPoint and the circle's position, and then get the magnitude to scale the direction from the overlap (from the distance of the radius and nearestPoint)
			else {
				overlapMagnitude = circle.getRadius() - distanceVector.length();

				return CollisionData{
					distanceVector.normalized(),
					overlapMagnitude
				};
			}
		}
			
		return std::nullopt;
	}

	// TODO: Create templated version of detectCollision() or some overloads for different scenarios.
}